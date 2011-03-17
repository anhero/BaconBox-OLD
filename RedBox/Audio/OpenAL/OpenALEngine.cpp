#include "OpenALEngine.h"

#include <fstream>

#include <cstring>
#include <cassert>

#include "Debug.h"

#include "BitHelper.h"
#include "WavHeader.h"

#include "SoundFX.h"
#include "SoundInfo.h"

#include "ResourceManager.h"

using namespace RedBox;

OpenALEngine* OpenALEngine::instance = NULL;

void OpenALEngine::setDefaultDevice(const std::string& newDevice) {
	defaultDevice = newDevice;
}

const std::vector<std::string>& OpenALEngine::getDeviceList() {
	// We only fill the list if it hasn't been filled yet.
	if(deviceList.size() == 0) {
		// Gets the list of all devices.
		const ALchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
		if(devices) {
			while(strlen(devices) > 0) {
				deviceList.push_back(devices);
				devices += strlen(devices) + 1;
			}
		}
	}
	return deviceList;
}

OpenALEngine* OpenALEngine::getInstance() {
	return instance;
}

SoundFX* OpenALEngine::getSoundFX(const std::string& key, bool survive) {
	SoundInfo* sndInfo = ResourceManager::getSound(key);
	if(sndInfo) {
		sources.push_back(new OpenALSoundFX());
		sources.back()->survives = survive;
		sources.back()->load(sndInfo->bufferId);
		return sources.back();
	} else {
		return NULL;
	}
}

OpenALEngine::OpenALEngine(): SoundEngine() {
	assert(!OpenALEngine::instance);
	OpenALEngine::instance = this;
}

OpenALEngine::~OpenALEngine() {
	// We delete all the sources.
	ALint bufferId;
	ALuint tmp;
	for(std::list<OpenALSoundFX*>::iterator i = sources.begin();
		i != sources.end(); i++) {
		// We make sure the source hasn't already been released.
		if (alIsSource((*i)->sourceId)) {
			// We make sure its buffer will be deleted.
			alGetSourcei((*i)->sourceId, AL_BUFFER, &bufferId);
			// We delete de source.
			alDeleteSources(1, &((*i)->sourceId));
			// We delete its buffer, if possible.
			if(bufferId != AL_NONE) {
				tmp = static_cast<ALuint>(bufferId);
				alDeleteBuffers(1, &tmp);
			}
		}
	}
	sources.clear();
	// We get the current context.
	ALCcontext* context = alcGetCurrentContext();
	// We check if it is valid.
	if(context) {
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		if(device) {
			alcCloseDevice(device);
		}
	}
}

void OpenALEngine::init() {
	ALCdevice* device = NULL;
	// We open the device.
	if(defaultDevice.empty()) {
		// If no default device to load is specified, we let OpenAL find the
		// default one.
		device = alcOpenDevice(NULL);
	} else {
		// If the user has specified a default device, we use it.
		device = alcOpenDevice(OpenALEngine::defaultDevice.c_str());
	}
	if(device) {
		// We create the context.
		ALCcontext* context = alcCreateContext(device, NULL);
		if(context) {
			// We activate the context.
			if(alcMakeContextCurrent(context)) {
				// We set the listener's position.
				alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
			} else {
				$ECHO("Failed to activate the OpenAL context.");
				// We close the device here because the destructor does not
				// close the device if no context was created.
				alcCloseDevice(device);
				// We destroy the context here because the destructor does not
				// destroy the context if the activation failed.
				alcDestroyContext(context);
			}
		} else {
			$ECHO("Failed to create the OpenAL context.");
			// We close the device here because the destructor does not
			// close the device if no context was created.
			alcCloseDevice(device);
		}
	} else {
		$ECHO("Failed to open the OpenAL audio device.");
	}
}

void OpenALEngine::update() {
	// We delete the sources of stopped sounds that must not survive.
	ALint state;
	// For each sound effect.
	for (std::list<OpenALSoundFX*>::iterator i = sources.begin();
		 i != sources.end(); i++) {
		// We get its current state.
		alGetSourcei((*i)->sourceId, AL_SOURCE_STATE, &state);
		// We check if it is not being played.
		if (state == AL_STOPPED) {
			// If we have to decrease its number of times left.
			if((*i)->nbTimesLeft > 0) {
				// We decrease it and replay it.
				--(*i)->nbTimesLeft;
				alSourcePlay((*i)->sourceId);
			} else if(!(*i)->survives) {
				// We delete the sound.
				alDeleteSources(1, &((*i)->sourceId));
				sources.erase(i);
			}
		}
	}
}

SoundInfo* OpenALEngine::loadSound(const std::string& filePath) {
	SoundInfo* newSnd = new SoundInfo();
	if(newSnd) {
		ALenum format;
		ALsizei bufferSize, freq;
		char* bufferData;
		// We load the wav file.
		OpenALEngine::loadWav(filePath, bufferData, bufferSize, format,
							  freq);
		// We check that the buffer was loaded correctly.
		if(bufferData) {
			alGenBuffers(1, &(newSnd->bufferId));
			alBufferData(newSnd->bufferId, format, bufferData, bufferSize,
						 freq);
		} else {
			delete newSnd;
			newSnd = NULL;
		}
	}
	return newSnd;
}

SoundInfo* OpenALEngine::loadSound(const SoundParameters& params) {
	return loadSound(params.path);
}

bool OpenALEngine::unloadSound(SoundInfo* sound) {
	// We release the buffer name.
	alDeleteBuffers(1, &sound->bufferId);
	// We check if it was released succesfully.
	return !alIsBuffer(sound->bufferId);
}

void OpenALEngine::deleteBufferSources(ALuint buffer) {
	ALint tmpBuffer;
	for(std::list<OpenALSoundFX*>::iterator i = sources.begin();
		i != sources.end(); i++) {
		alGetSourcei((*i)->sourceId, AL_BUFFER, &tmpBuffer);
		if (static_cast<ALuint>(tmpBuffer) == buffer) {
			alDeleteSources(1, &((*i)->sourceId));
			sources.erase(i);
		}
	}
}

void OpenALEngine::loadWav(const std::string& filePath,
						   char*& bufferData,
						   ALsizei& bufferSize,
						   ALenum& format,
						   ALsizei& freq) {
	// We open the wav file.
	std::fstream binFile(filePath.c_str(), std::ios::binary|std::ios::in);
	// We check if the file is correctly opened.
	if (binFile.is_open() && binFile.good()) {
		// We get the file's starting position.
		long begin = binFile.tellg();
		// We move at the end of the file.
		binFile.seekg(0, std::ios::end);
		// We get the last byte's position.
		long end = binFile.tellg();
		// We go back to the start of the file.
		binFile.seekg(0, std::ios::beg);
		// Will contain the wav header information.
		WavHeader wav;
		// We read the wav header information from the file and put it in the
		// wav variable.
		binFile.read(reinterpret_cast<char*>(&wav), sizeof(wav));
		
		// We swap the endian for the header informations that are in big
		// endian.
		BitHelper::endianSwap(wav.chunkId);
		BitHelper::endianSwap(wav.format);
		BitHelper::endianSwap(wav.subchunk1Id);
		BitHelper::endianSwap(wav.subchunk2Id);
		
		// We get the number of channels.
		if(wav.nbChannels == 1) {
			format = AL_FORMAT_MONO16;
		} else {
			format = AL_FORMAT_STEREO16;
		}
		
		// We get the sample rate.
		freq = wav.sampleRate;
		
		// We check to calculate the buffer size. The information in the header
		// can sometimes be wrong, so we can calculate it using the file's size
		// and substracting the header's size to it.
		bufferSize = end - begin - sizeof(wav);
		// We allocate memory for the buffe data.
		bufferData = new char[bufferSize];
		// We read the data from the file.
		binFile.read(bufferData, bufferSize);
		// If there was an error while loading the buffer.
		if(binFile.rdstate()) {
			// We delete the buffer and set it to NULL.
			delete[] bufferData;
			bufferData = NULL;
			$ECHO("Failed to read the buffer data from the wave file: " <<
				  filePath);
		}
		// We close the file.
		binFile.close();
	} else {
		$ECHO("Failed to open the file: " << filePath);
	}
}

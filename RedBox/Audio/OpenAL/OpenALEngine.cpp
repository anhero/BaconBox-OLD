#include "OpenALEngine.h"

#include <fstream>

#include <cstring>
#include <cassert>

#include "Debug.h"

#include "OpenALSoundFX.h"
#include "BitHelper.h"
#include "WavHeader.h"

using namespace RedBox;

OpenALEngine* OpenALEngine::instance = NULL;

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
	// We delete the sources of stopped sounds.
	ALint state;
	for (std::list<ALuint>::iterator i = sources.begin(); i != sources.end(); i++) {
		alGetSourcei(*i, AL_SOURCE_STATE, &state);
		if (state == AL_STOPPED) {
			alDeleteSources(1, &(*i));
			sources.erase(i);
		}
	}
}

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

void OpenALEngine::addSource(ALuint newSource) {
	sources.push_back(newSource);
}

void OpenALEngine::deleteBufferSources(ALuint buffer) {
	ALint tmpBuffer;
	for(std::list<ALuint>::iterator i = sources.begin(); i != sources.end(); i++) {
		alGetSourcei(*i, AL_BUFFER, &tmpBuffer);
		if (tmpBuffer == buffer) {
			alDeleteSources(1, &(*i));
			sources.erase(i);
		}
	}
	
}

OpenALEngine* OpenALEngine::getInstance() {
	return instance;
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

OpenALEngine::OpenALEngine(): AudioEngine() {
	assert(!OpenALEngine::instance);
	OpenALEngine::instance = this;
}

SoundFX* OpenALEngine::loadSoundFX(const std::string& filePath) {
	SoundInfo snd;
	snd.path = filePath;
	return loadSoundFX(snd);
}

SoundFX* OpenALEngine::loadSoundFX(const SoundInfo& info) {
	// We allocate a new sound effect.
	OpenALSoundFX* snd = new OpenALSoundFX();
	// We check if it was correctly created.
	if(snd) {
		// We attempt to load the sound effect and delete it if it didn't work.
		if(!snd->load(info.path)) {
			delete snd;
			snd = NULL;
		}
	}
	return snd;
}

BackgroundMusic* OpenALEngine::loadBackgroundMusic(const std::string& filePath) {
	return NULL;
}
BackgroundMusic* OpenALEngine::loadBackgroundMusic(const MusicInfo& info) {
	return NULL;
}

OpenALEngine::~OpenALEngine() {
	// We delete all the sources.
	for(std::list<ALuint>::iterator i = sources.begin(); i != sources.end(); i++) {
		alDeleteSources(1, &(*i));
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
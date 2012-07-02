#include "BaconBox/Audio/OpenAL/OpenALEngine.h"

#include "BaconBox/PlatformFlagger.h"

#include <fstream>
#include <algorithm>
#include <cstring>
#include <cassert>

#include "BaconBox/Console.h"

#include "BaconBox/Audio/OpenAL/RBOpenAL.h"

#include "BaconBox/Helper/BitHelper.h"
#include "BaconBox/Audio/OpenAL/WavHeader.h"

#include "BaconBox/Audio/SoundFX.h"
#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/NullAudio.h"
#include "BaconBox/Audio/OpenAL/OpenALSoundFX.h"

#include "BaconBox/ResourceManager.h"

namespace BaconBox {
	int OpenALEngine::openALToBaconBoxVolume(float openALVolume) {
		if (openALVolume < 0.0f) {
			return Sound::MIN_VOLUME;

		} else if (openALVolume > 1.0f) {
			return Sound::MAX_VOLUME;

		} else {
			return static_cast<int>(openALVolume * static_cast<float>(Sound::MAX_VOLUME));
		}
	}

	float OpenALEngine::baconBoxToOpenALVolume(int baconBoxVolume) {
		if (baconBoxVolume < Sound::MIN_VOLUME) {
			return 0.0f;

		} else if (baconBoxVolume > Sound::MAX_VOLUME) {
			return 1.0f;

		} else {
			return static_cast<float>(baconBoxVolume) / static_cast<float>(Sound::MAX_VOLUME);
		}
	}

	void OpenALEngine::setDefaultDevice(const std::string &newDevice) {
		defaultDevice = newDevice;
	}

	const std::vector<std::string>& OpenALEngine::getDeviceList() {
		// We only fill the list if it hasn't been filled yet.
		if (deviceList.empty()) {
			// Gets the list of all devices.
			const ALchar *devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

			if (devices) {
				while (strlen(devices) > 0) {
					deviceList.push_back(devices);
					devices += strlen(devices) + 1;
				}
			}
		}

		return deviceList;
	}

	SoundFX *OpenALEngine::getSoundFX(const std::string &key, bool survive) {
		SoundInfo *sndInfo = ResourceManager::getSound(key);

		if (sndInfo) {
			sources.push_back(new OpenALSoundFX());
			sources.back()->survives = survive;
			sources.back()->load(sndInfo->bufferId);
			return sources.back();

		} else {
			NullAudio *nullAudio = new NullAudio();

			if (!survive) {
				nullsToClean.push_back(nullAudio);
			}

			return nullAudio;
		}
	}

	void OpenALEngine::setSoundVolume(int newSoundVolume) {
		this->SoundEngine::setSoundVolume(newSoundVolume);

		if (!this->SoundEngine::isMuted()) {
			alListenerf(AL_GAIN, static_cast<float>(getSoundVolume()) / static_cast<float>(Sound::MAX_VOLUME));
		}
	}

	OpenALEngine::OpenALEngine(): SoundEngine() {
		ALCdevice *device = NULL;

		// We open the device.
		if (defaultDevice.empty()) {
			// If no default device to load is specified, we let OpenAL find the
			// default one.
			device = alcOpenDevice(NULL);

		} else {
			// If the user has specified a default device, we use it.
			device = alcOpenDevice(OpenALEngine::defaultDevice.c_str());
		}

		if (device) {
			// We create the context.
			ALCcontext *context = alcCreateContext(device, NULL);

			if (context) {
				// We activate the context.
				if (alcMakeContextCurrent(context)) {
					// We set the listener's position.
					alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);

				} else {
					Console::print("Failed to activate the OpenAL context.");
					// We close the device here because the destructor does not
					// close the device if no context was created.
					alcCloseDevice(device);
					// We destroy the context here because the destructor does not
					// destroy the context if the activation failed.
					alcDestroyContext(context);
				}

			} else {
				Console::print("Failed to create the OpenAL context.");
				// We close the device here because the destructor does not
				// close the device if no context was created.
				alcCloseDevice(device);
			}

		} else {
			Console::print("Failed to open the OpenAL audio device.");
		}
	}

	OpenALEngine::~OpenALEngine() {
		// We delete all the sources.
		ALint bufferId;
		ALuint tmp;

		for (std::list<OpenALSoundFX *>::iterator i = sources.begin();
		     i != sources.end(); ++i) {
			// We make sure the source hasn't already been released.
			if (alIsSource((*i)->sourceId)) {
				// We make sure its buffer will be deleted.
				alGetSourcei((*i)->sourceId, AL_BUFFER, &bufferId);
				// We delete de source.
				alDeleteSources(1, &((*i)->sourceId));

				// We delete its buffer, if possible.
				if (bufferId != AL_NONE) {
					tmp = static_cast<ALuint>(bufferId);
					alDeleteBuffers(1, &tmp);
				}
			}
		}

		sources.clear();
		// We get the current context.
		ALCcontext *context = alcGetCurrentContext();

		// We check if it is valid.
		if (context) {
			ALCdevice *device = alcGetContextsDevice(context);
			alcMakeContextCurrent(NULL);
			alcDestroyContext(context);

			if (device) {
				alcCloseDevice(device);
			}
		}
	}

	void OpenALEngine::update() {
		{
			// We delete the sources of stopped sounds that must not survive.
			ALint state;
			// For each sound effect.
			std::list<OpenALSoundFX *>::iterator i = sources.begin();

			while (i != sources.end()) {
				// We get its current state.
				alGetSourcei((*i)->sourceId, AL_SOURCE_STATE, &state);

				// We check if it is not being played.
				if (state == AL_STOPPED) {
					// If we have to decrease its number of times left.
					if ((*i)->nbTimesLeft > 0) {
						// We decrease it and replay it.
						--(*i)->nbTimesLeft;
						alSourcePlay((*i)->sourceId);
						++i;

					} else if (!(*i)->survives) {
						// We delete the sound.
						alDeleteSources(1, &((*i)->sourceId));
						delete *i;
						i = sources.erase(i);

					} else {
						++i;
					}

				} else {
					++i;
				}
			}
		}

		for (std::list<NullAudio *>::iterator i = nullsToClean.begin();
		     i != nullsToClean.end(); ++i) {
			if (*i) {
				delete *i;
			}
		}

		nullsToClean.clear();
	}

	SoundInfo *OpenALEngine::loadSound(const std::string &filePath) {
		SoundInfo *newSnd = NULL;

		ALenum format;
		ALsizei bufferSize, freq;
		char *bufferData;
		// We load the wav file.
		OpenALEngine::loadWav(filePath, bufferData, bufferSize, format,
		                      freq);

		// We check that the buffer was loaded correctly.
		if (bufferData) {
			newSnd = new SoundInfo();
			alGenBuffers(1, &(newSnd->bufferId));
			alBufferData(newSnd->bufferId, format, bufferData, bufferSize,
			             freq);
		}

		return newSnd;
	}

	SoundInfo *OpenALEngine::loadSound(const SoundParameters &params) {
		return loadSound(params.path);
	}

	bool OpenALEngine::unloadSound(SoundInfo *sound) {
		// We release the buffer name.
		alDeleteBuffers(1, &sound->bufferId);

		// We check if there are still sources using this buffer.
		if (alGetError() == AL_INVALID_NAME) {
			// If so, we delete its sources and re-try to release the buffer.
			deleteBufferSources(sound->bufferId);
			alDeleteBuffers(1, &sound->bufferId);
		}

		// We check if it was released successfully.
		return !alIsBuffer(sound->bufferId);
	}

	class PredBufferSource {
	public:
		PredBufferSource(ALuint newBuffer) : buffer(newBuffer) {
		}
		bool operator()(OpenALSoundFX *sfx) const {
			bool result = false;

			if (sfx) {
				ALint tmpBuffer;
				alGetSourcei(sfx->getSourceId(), AL_BUFFER, &tmpBuffer);

				if (static_cast<ALuint>(tmpBuffer) == buffer) {
					alDeleteSources(1, &(sfx->getSourceId()));
					result = true;
				}
			}

			return result;
		}
	private:
		ALuint buffer;
	};

	void OpenALEngine::deleteBufferSources(ALuint buffer) {
		std::list<OpenALSoundFX *>::iterator pos = std::remove_if(sources.begin(), sources.end(), PredBufferSource(buffer));
		sources.erase(pos, sources.end());
	}

	void OpenALEngine::loadWav(const std::string &filePath,
	                           char*& bufferData,
	                           ALsizei &bufferSize,
	                           ALenum &format,
	                           ALsizei &freq) {
		// We open the wav file.
		std::fstream binFile(filePath.c_str(), std::ios::binary | std::ios::in);

		// We check if the file is correctly opened.
		if (binFile.is_open() && binFile.good()) {
			// We get the file's starting position.
			binFile.seekg(0, std::ios::beg);
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
			binFile.read(reinterpret_cast<char *>(&wav), sizeof(WavHeader));

			if (wav.blockAlign != wav.nbChannels * (wav.bitsPerSample / 8)) {
				wav.blockAlign = wav.nbChannels * (wav.bitsPerSample / 8);
				Console::print("The wav's block alignment was wrong, we calculated the correct value for this wav file: ");
				Console::println(filePath);
			}

			if (wav.byteRate != wav.sampleRate * wav.nbChannels * (wav.bitsPerSample / 8)) {
				wav.byteRate = wav.sampleRate * wav.nbChannels * (wav.bitsPerSample / 8);
				Console::print("The wav's byte rate was wrong, we calculated the correct value for this wav file: ");
				Console::println(filePath);
			}

			// We check what wav we are reading.
			if (wav.chunkId == OpenALEngine::CHUNK_ID_RIFF ||
			    wav.chunkId == BitHelper::otherEndian(OpenALEngine::CHUNK_ID_RIFF)) {
				// We check what format we are reading.
				if (wav.format == OpenALEngine::FORMAT_WAVE ||
				    wav.format == BitHelper::otherEndian(OpenALEngine::FORMAT_WAVE)) {
					// We swap the endian for the header informations that are in big
					// endian.
					BitHelper::endianSwap(wav.subchunk1Id);
					BitHelper::endianSwap(wav.subchunk2Id);

					// We get the number of channels.
					if (wav.nbChannels == 1) {
						format = AL_FORMAT_MONO16;

					} else {
						format = AL_FORMAT_STEREO16;
					}

					// We get the sample rate.
					freq = wav.sampleRate;

					// We check to calculate the buffer size. The information in the header
					// can sometimes be wrong, so we can calculate it using the file's size
					// and subtracting the header's size to it.
					bufferSize = end - begin - sizeof(WavHeader);
					// We allocate memory for the buffer data.
					bufferData = new char[bufferSize];
					// We read the data from the file.
					binFile.read(bufferData, bufferSize);

					// If there was an error while loading the buffer.
					if (binFile.rdstate()) {
						// We delete the buffer and set it to NULL.
						delete[] bufferData;
						bufferData = NULL;
						Console::print("Failed to read the buffer data from the wave file: " +
						               filePath);
					}

				} else {
					char *format = reinterpret_cast<char *>(&wav.format);
					Console::print("Unknown wav format : " + format[0] + format[1] + format[2] + format[3]);
				}

			} else {
				char *chunkId = reinterpret_cast<char *>(&wav.chunkId);
				Console::print("Unknown wav chunk ID : " + chunkId[0] + chunkId[1] + chunkId[2] + chunkId[3]);
			}

			// We close the file.
			binFile.close();

		} else {
			Console::print("Failed to open the file: " + filePath);
		}
	}
}

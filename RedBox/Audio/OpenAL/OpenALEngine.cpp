#include "OpenALEngine.h"

#include "Debug.h"

using namespace RedBox;

ALCchar* OpenALEngine::defaultDevice = NULL;

void OpenALEngine::init() {
	// We open the device.
	ALCdevice* device = alcOpenDevice(OpenALEngine::defaultDevice);
	if(device) {
		// We create the context.
		ALCcontext* context = alcCreateContext(device, NULL);
		if(context) {
			// We activate the context.
			if(!alcMakeContextCurrent(context)) {
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
}

void OpenALEngine::setDefaultDevice(ALCchar* newDevice) {
	defaultDevice = newDevice;
}

OpenALEngine::OpenALEngine(): AudioEngine() {
}

SoundFX* OpenALEngine::loadSoundFX(const std::string& filePath) {
	return NULL;
}

SoundFX* OpenALEngine::loadSoundFX(const SoundInfo& info) {
	return NULL;
}

BackgroundMusic* loadBackgroundMusic(const std::string& filePath) {
	return NULL;
}
BackgroundMusic* loadBackgroundMusic(const MusicInfo& info) {
	return NULL;
}

OpenALEngine::~OpenALEngine() {
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
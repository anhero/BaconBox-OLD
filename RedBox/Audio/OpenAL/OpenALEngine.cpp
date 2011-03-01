#include "OpenALEngine.h"

#include <cstring>

#include "Debug.h"

#include "OpenALSoundFX.h"

using namespace RedBox;

std::string OpenALEngine::defaultDevice = "";
std::vector<std::string> OpenALEngine::deviceList = std::vector<std::string>();


void OpenALEngine::init() {
	// We open the device.
	ALCdevice* device = alcOpenDevice(OpenALEngine::defaultDevice.c_str());
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

void OpenALEngine::setDefaultDevice(const std::string& newDevice) {
	defaultDevice = newDevice;
}

const std::vector<std::string>& OpenALEngine::getDeviceList() {
	if(deviceList.size() == 0) {
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

OpenALEngine::OpenALEngine(): AudioEngine() {
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
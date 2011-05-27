#include "NullAudioEngine.h"

#include "Console.h"

#include "SoundInfo.h"
#include "MusicInfo.h"
#include "NullAudio.h"
#include "ResourceManager.h"

using namespace RedBox;

SoundFX* NullAudioEngine::getSoundFX(const std::string& key, bool survive) {
	NullAudio* result = new NullAudio();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			Console::print("Got a sound effect from the key: " + key +
						   " that must " + ((survive)?(""):("not ")) +
						   "survive.");
		} else {
			delete result;
			result = NULL;
			Console::print("Tried to get a sound effect from an invalid key: " +
						   key);
			Console::printTrace();
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::print("Failed to allocate memory for the new sound effect: " +
					   key);
		Console::printTrace();
	}

	return result;
}

BackgroundMusic* NullAudioEngine::getBackgroundMusic(const std::string& key,
													 bool survive) {
	NullAudio* result = new NullAudio();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			Console::print("Got a background music from the key: " + key +
						   " that must " + ((survive)?(""):("not ")) +
						   "survive.");
		} else {
			delete result;
			result = NULL;
			Console::print("Tried to get a music from an invalid key: " + key);
			Console::printTrace();
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::print("Failed to allocate memory for the new music: " + key);
		Console::printTrace();
	}

	return result;
}

NullAudioEngine::NullAudioEngine() : SoundEngine(), MusicEngine() {
	Console::print("NullAudioEngine::NullAudioEngine()");
}

void NullAudioEngine::init() {
	Console::print("NullAudioEngine::init()");
}

void NullAudioEngine::update() {
	// For each sound (music or sound effect).
	std::list<NullAudio*>::iterator i = audios.begin();
	while(i != audios.end()) {
		// We make sure the pointer is valid.
		if(*i) {
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				delete *i;
				i = audios.erase(i);
			} else {
				++i;
			}
		} else {
			// If the pointer is invalid (which should not happen), we remove
			// it from the list.
			i = audios.erase(i);
		}
	}
}

NullAudioEngine::~NullAudioEngine() {
	Console::print("NullAudioEngine::~NullAudioEngine()");
}

SoundInfo* NullAudioEngine::loadSound(const std::string& filePath) {
	Console::print("NullAudioEngine::loadSound(filePath: " + filePath + ")");
	return new SoundInfo();
}

SoundInfo* NullAudioEngine::loadSound(const SoundParameters& params) {
	Console::print("NullAudioEngine::loadSound(params.name: " + params.name +
				   ")");
	return new SoundInfo();
}

bool NullAudioEngine::unloadSound(SoundInfo* sound) {
	Console::print("NullAudioEngine::unloadSound(sound: " +
				   Console::toString(sound) + ")");
	return true;
}

MusicInfo* NullAudioEngine::loadMusic(const std::string& filePath) {
	Console::print("NullAudioEngine::loadMusic(filePath: " + filePath + ")");
	return new MusicInfo();
}

MusicInfo* NullAudioEngine::loadMusic(const MusicParameters& params) {
	Console::print("NullAudioEngine::loadMusic(params.name: " + params.name +
				   ")");
	return new MusicInfo();
}

bool NullAudioEngine::unloadMusic(MusicInfo* music) {
	Console::print("NullAudioEngine::unloadMusic(music: " +
				   Console::toString(music) + ")");
	return true;
}


#include "BaconBox/Audio/NullAudioEngine.h"

#include "BaconBox/Console.h"

#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Audio/NullAudio.h"
#include "BaconBox/ResourceManager.h"

using namespace BaconBox;

NullAudioEngine& NullAudioEngine::getInstance() {
	static NullAudioEngine instance;
	return instance;
}

SoundFX* NullAudioEngine::getSoundFX(const std::string& key, bool survive) {
	NullAudio* result = new NullAudio();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			Console::println("Got a sound effect from the key: " + key +
						   " that must " + ((survive)?(""):("not ")) +
						   "survive.");
		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a sound effect from an invalid key: " +
						   key);
			Console::printTrace();
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new sound effect: " +
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
			Console::println("Got a background music from the key: " + key +
						   " that must " + ((survive)?(""):("not ")) +
						   "survive.");
		} else {
			delete result;
			result = NULL;
			Console::println("Tried to get a music from an invalid key: " + key);
			Console::printTrace();
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::println("Failed to allocate memory for the new music: " + key);
		Console::printTrace();
	}

	return result;
}

NullAudioEngine::NullAudioEngine() : SoundEngine(), MusicEngine() {
	Console::println("NullAudioEngine::NullAudioEngine()");
}

NullAudioEngine::~NullAudioEngine() {
	Console::println("NullAudioEngine::~NullAudioEngine()");
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

SoundInfo* NullAudioEngine::loadSound(const std::string& filePath) {
	Console::println("NullAudioEngine::loadSound(filePath: " + filePath + ")");
	return new SoundInfo();
}

SoundInfo* NullAudioEngine::loadSound(const SoundParameters& params) {
	Console::println("NullAudioEngine::loadSound(params.name: " + params.name +
				   ")");
	return new SoundInfo();
}

bool NullAudioEngine::unloadSound(SoundInfo* sound) {
	Console::println("NullAudioEngine::unloadSound(sound: " +
				   Console::toString(sound) + ")");
	return true;
}

MusicInfo* NullAudioEngine::loadMusic(const std::string& filePath) {
	Console::println("NullAudioEngine::loadMusic(filePath: " + filePath + ")");
	return new MusicInfo();
}

MusicInfo* NullAudioEngine::loadMusic(const MusicParameters& params) {
	Console::println("NullAudioEngine::loadMusic(params.name: " + params.name +
				   ")");
	return new MusicInfo();
}

bool NullAudioEngine::unloadMusic(MusicInfo* music) {
	Console::println("NullAudioEngine::unloadMusic(music: " +
				   Console::toString(music) + ")");
	return true;
}


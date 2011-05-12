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
			Console::Print("Got a sound effect from the key: " + key +
						   " that must " + ((survive)?(""):("not ")) +
						   "survive.");
		} else {
			delete result;
			result = NULL;
			Console::Print("Tried to get a sound effect from an invalid key: " +
						   key);
			Console::PrintTrace();
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::Print("Failed to allocate memory for the new sound effect: " +
					   key);
		Console::PrintTrace();
	}

	return result;
}

BackgroundMusic* NullAudioEngine::getBackgroundMusic(const std::string& key,
													 bool survive) {
	NullAudio* result = new NullAudio();

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			Console::Print("Got a background music from the key: " + key +
						   " that must " + ((survive)?(""):("not ")) +
						   "survive.");
		} else {
			delete result;
			result = NULL;
			Console::Print("Tried to get a music from an invalid key: " + key);
			Console::PrintTrace();
		}

		if(!survive) {
			audios.push_back(result);
		}
	} else {
		Console::Print("Failed to allocate memory for the new music: " + key);
		Console::PrintTrace();
	}

	return result;
}

NullAudioEngine::NullAudioEngine() : SoundEngine(), MusicEngine() {
	Console::Print("NullAudioEngine::NullAudioEngine()");
}

void NullAudioEngine::init() {
	Console::Print("NullAudioEngine::init()");
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
	Console::Print("NullAudioEngine::~NullAudioEngine()");
}

SoundInfo* NullAudioEngine::loadSound(const std::string& filePath) {
	Console::Print("NullAudioEngine::loadSound(filePath: " + filePath + ")");
	return new SoundInfo();
}

SoundInfo* NullAudioEngine::loadSound(const SoundParameters& params) {
	Console::Print("NullAudioEngine::loadSound(params.name: " + params.name +
				   ")");
	return new SoundInfo();
}

bool NullAudioEngine::unloadSound(SoundInfo* sound) {
	Console::Print("NullAudioEngine::unloadSound(sound: " +
				   Console::ToString(sound) + ")");
	return true;
}

MusicInfo* NullAudioEngine::loadMusic(const std::string& filePath) {
	Console::Print("NullAudioEngine::loadMusic(filePath: " + filePath + ")");
	return new MusicInfo();
}

MusicInfo* NullAudioEngine::loadMusic(const MusicParameters& params) {
	Console::Print("NullAudioEngine::loadMusic(params.name: " + params.name +
				   ")");
	return new MusicInfo();
}

bool NullAudioEngine::unloadMusic(MusicInfo* music) {
	Console::Print("NullAudioEngine::unloadMusic(music: " +
				   Console::ToString(music) + ")");
	return true;
}


#include "PlatformFlagger.h"

#include "NullAudioEngine.h"

#include "Debug.h"

#include "ResourceManager.h"
#include "SoundInfo.h"
#include "MusicInfo.h"
#include "AudioState.h"
#include "NullAudio.h"
#include "Sound.h"

using namespace RedBox;

NullAudioEngine* NullAudioEngine::instance = NULL;

NullAudioEngine* NullAudioEngine::getInstance() {
	if(instance == NULL) {
		instance = new NullAudioEngine();
	}

	return instance;
}

SoundFX* NullAudioEngine::getSoundFX(const std::string& key, bool survive) {
	NullAudio* nullSound = new NullAudio();
	SoundFX* result = nullSound;

	if(result) {
		SoundInfo* info = ResourceManager::getSound(key);

		if(info) {
			//nullSound->load(info->data);

		} else {
			delete result;
			result = new NullAudio();
			RB_ECHO("Tried to get a sound effect from an invalid key: " <<
					key);
		}
		if(!survive) {
			sounds.push_back(result);
		}
	} else {
		RB_ECHO("Failed to allocate memory for the new sound effect: " <<
				key);
	}

	return result;
}
BackgroundMusic* NullAudioEngine::getBackgroundMusic(const std::string& key,
        bool survive) {
	NullAudio* nullMusic = new NullAudio();
	BackgroundMusic* result = nullMusic;

	if(result) {
		MusicInfo* info = ResourceManager::getMusic(key);

		if(info) {
			//nullMusic->load(info->music);

		} else {
			delete result;
			result = new NullAudio();
			RB_ECHO("Tried to get a background music from an invalid key: " <<
					key);
		}
		if(!survive) {
			sounds.push_back(result);
		}
	} else {
		RB_ECHO("Failed to allocate memory for the new background music: " <<
				key);
	}

	return result;
}

void NullAudioEngine::askForDisconnect() {
	disconnect = true;
}

NullAudioEngine::NullAudioEngine() : SoundEngine(), MusicEngine(), disconnect(false) {
	lastFadeTick = 0;
	lastFadeTick -= lastFadeTick % NB_TICKS_PER_FADE;
}

void NullAudioEngine::init() {
	RB_ECHO("NullAudioEngine::init();");
}

void NullAudioEngine::update() {
	// We update the pause/resume fading.
	if(true) {
		lastFadeTick += NB_TICKS_PER_FADE;
		fadeUpdate.shoot(lastFadeTick);

		if(disconnect) {
			fadeUpdate.disconnectAll();
		}
	}

	// For each sound (music or sound effect).
	std::list<Sound*>::iterator i = sounds.begin();
	while(i != sounds.end()) {
		// We make sure the pointer is valid.
		if(*i) {
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				delete *i;
				i = sounds.erase(i);
			} else {
				++i;
			}
		} else {
			// If the pointer is invalid (which should not happen), we remove
			// it from the list.
			i = sounds.erase(i);
		}
	}
}

NullAudioEngine::~NullAudioEngine() {
	Mix_CloseAudio();
}

SoundInfo* NullAudioEngine::loadSound(const std::string& filePath) {
	SoundInfo* result = new SoundInfo();
	result->data = Mix_LoadWAV(filePath.c_str());

	// We make sure the sound file is correctly loaded.
	if(!result->data) {
		// We delete the resulting sound info.
		delete result;
		result = NULL;
		RB_ECHO("Unable to load sound effect: " << filePath <<
		        " ...");
	}

	return result;
}

SoundInfo* NullAudioEngine::loadSound(const SoundParameters& params) {
	return loadSound(params.path);
}

bool NullAudioEngine::unloadSound(SoundInfo* sound) {
	if(sound && sound->data) {
		Mix_FreeChunk(sound->data);
	}

	return true;
}

MusicInfo* NullAudioEngine::loadMusic(const std::string& filePath) {
	MusicInfo* result = new MusicInfo();

	if(result) {
		result->music = Mix_LoadMUS(filePath.c_str());

		if(!result->music) {
			delete result;
			result = NULL;
			RB_ECHO("Unable to load music file: " << filePath << std::endl <<
			        "... ");
		}
	} else {
		RB_ECHO("Could not allocate memory for the music info for the file: " << filePath);
	}

	return result;
}

MusicInfo* NullAudioEngine::loadMusic(const MusicParameters& params) {
	return loadMusic(params.filePath);
}

bool NullAudioEngine::unloadMusic(MusicInfo* music) {
	if(music && music->music) {
		Mix_FreeMusic(music->music);
	}

	return true;
}


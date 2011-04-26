#include "PlatformFlagger.h"

#ifdef RB_SDL

#include "SDLMixerEngine.h"

#include <SDL/SDL.h>

#include "Debug.h"

#include "ResourceManager.h"
#include "SoundInfo.h"
#include "MusicInfo.h"
#include "AudioState.h"

#include "SDLMixerBackgroundMusic.h"

using namespace RedBox;

SDLMixerEngine* SDLMixerEngine::instance = NULL;

SDLMixerEngine* SDLMixerEngine::getInstance() {
	if(instance == NULL) {
		instance = new SDLMixerEngine();
	}
	return instance;
}

SoundFX* SDLMixerEngine::getSoundFX(const std::string& key, bool survive) {
	return 0;
}
BackgroundMusic* SDLMixerEngine::getBackgroundMusic(const std::string& key,
													bool survive) {
	SDLMixerBackgroundMusic* result = new SDLMixerBackgroundMusic();
	if(result) {
		MusicInfo* info = ResourceManager::getMusic(key);
		if(info) {
			result->load(info->music);
		} else {
			delete result;
			result = NULL;
			RB_ECHO("Tried to get a background music from an invalid key: " <<
					key)
		}
	} else {
		RB_ECHO("Failed to allocate memory for the new background music: " <<
				key)
	}
	return result;
}

void SDLMixerEngine::askForDisconnect() {
	disconnect = true;
}

SDLMixerEngine::SDLMixerEngine() : SoundEngine(), MusicEngine(), disconnect(false) {
	lastFadeTick = SDL_GetTicks();
	lastFadeTick -= lastFadeTick % NB_TICKS_PER_FADE;
}

void SDLMixerEngine::init() {
	// We initialize SDL_mixer.
	if(!Mix_OpenAudio(SDLMixerEngine::AUDIO_RATE, SDLMixerEngine::AUDIO_FORMAT, SDLMixerEngine::AUDIO_CHANNELS, SDLMixerEngine::AUDIO_BUFFERS)) {
		// We set the function to call when a music is stopped.
		Mix_HookMusicFinished(SDLMixerBackgroundMusic::stoppedCurrentMusic);
	} else {
		RB_ECHO("Unable to initialize audio: " << Mix_GetError());
	}
}

void SDLMixerEngine::update() {
	// We update the pause/resume fading.
	if (SDL_GetTicks() > lastFadeTick + NB_TICKS_PER_FADE) {
		lastFadeTick += NB_TICKS_PER_FADE;
		fadeUpdate.shoot(lastFadeTick);
		if(disconnect) {
			fadeUpdate.disconnectAll();
		}
	}
	// For each sound effect.
	for (std::list<SDLMixerBackgroundMusic*>::iterator i = musics.begin();
		 i != musics.end(); i++) {
		// We make sure the pointer is valid.
		if(*i) {
			// If the music is set at stopped.
			if((*i)->getCurrentState() == AudioState::STOPPED) {
				// We delete the background music.
				delete *i;
				musics.erase(i);
			}
		} else {
			// If it's invalid, we remove it.
			musics.erase(i);
		}
	}
}

SDLMixerEngine::~SDLMixerEngine() {
	Mix_CloseAudio();
}

SoundInfo* SDLMixerEngine::loadSound(const std::string& filePath) {
	return 0;
}

SoundInfo* SDLMixerEngine::loadSound(const SoundParameters& params) {
	return 0;
}

bool SDLMixerEngine::unloadSound(SoundInfo* sound) {
	return 0;
}

MusicInfo* SDLMixerEngine::loadMusic(const std::string& filePath) {
	MusicInfo* result = new MusicInfo();
	if(result) {
		result->music = Mix_LoadMUS(filePath.c_str());
		if(!result->music) {
			delete result;
			result = NULL;
			RB_ECHO("Unable to load music file: " << filePath << std::endl <<
					" with the SDL_mixer error: " << Mix_GetError());
		}
	} else {
		RB_ECHO("Could not allocate memory for the music info for the file: " <<
				filePath);
	}
	return result;
}

MusicInfo* SDLMixerEngine::loadMusic(const MusicParameters& params) {
	return loadMusic(params.filePath);
}

bool SDLMixerEngine::unloadMusic(MusicInfo* music) {
	if(music && music->music) {
		Mix_FreeMusic(music->music);
	}
	return true;
}

#endif

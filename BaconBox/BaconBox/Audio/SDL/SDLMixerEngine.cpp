#include "BaconBox/Audio/SDL/SDLMixerEngine.h"

#include "BaconBox/PlatformFlagger.h"

#include <SDL2/SDL.h>

#include "BaconBox/Console.h"

#include "BaconBox/ResourceManager.h"
#include "BaconBox/Audio/SoundInfo.h"
#include "BaconBox/Audio/MusicInfo.h"
#include "BaconBox/Audio/AudioState.h"
#include "BaconBox/Audio/NullAudio.h"
#include "BaconBox/Audio/Sound.h"

#include "BaconBox/Audio/SDL/SDLMixerBackgroundMusic.h"
#include "BaconBox/Audio/SDL/SDLMixerSoundFX.h"

namespace BaconBox {
	SDLMixerEngine *SDLMixerEngine::instance = NULL;

	SDLMixerEngine *SDLMixerEngine::getInstance() {
		return instance;
	}

	int SDLMixerEngine::sdlToBaconBoxVolume(int sdlVolume) {
		if (sdlVolume < 0) {
			return Sound::MIN_VOLUME;

		} else if (sdlVolume > MIX_MAX_VOLUME) {
			return Sound::MAX_VOLUME;

		} else {
			return (sdlVolume * Sound::MAX_VOLUME) / MIX_MAX_VOLUME;
		}
	}

	int SDLMixerEngine::baconBoxToSdlVolume(int baconBoxVolume) {
		if (baconBoxVolume <= Sound::MIN_VOLUME) {
			return 0;

		} else if (baconBoxVolume >= Sound::MAX_VOLUME) {
			return MIX_MAX_VOLUME;

		} else {
			return (baconBoxVolume * MIX_MAX_VOLUME) / Sound::MAX_VOLUME;
		}
	}

	SoundFX *SDLMixerEngine::getSoundFX(const std::string &key, bool survive) {
		SDLMixerSoundFX *sdlSound = new SDLMixerSoundFX();
		SoundFX *result = sdlSound;

		if (result) {
			SoundInfo *info = ResourceManager::getSound(key);

			if (info) {
				sdlSound->load(info->data);

			} else {
				delete result;
				result = new NullAudio();
				Console::println("Tried to get a sound effect from an invalid key: "
				                 + key);
				Console::printTrace();
			}

			if (!survive) {
				sounds.push_back(result);
			}

		} else {
			Console::println("Failed to allocate memory for the new sound effect: "
			                 + key);
			Console::printTrace();
		}

		return result;
	}
	BackgroundMusic *SDLMixerEngine::getBackgroundMusic(const std::string &key,
	                                                    bool survive) {
		SDLMixerBackgroundMusic *sdlMusic = new SDLMixerBackgroundMusic();
		BackgroundMusic *result = sdlMusic;

		if (result) {
			MusicInfo *info = ResourceManager::getMusic(key);

			if (info) {
				sdlMusic->load(info->music);

			} else {
				delete result;
				result = new NullAudio();
				Console::println("Tried to get a background music from an invalid key: "
				                 + key);
				Console::printTrace();
			}

			if (!survive) {
				sounds.push_back(result);
			}

		} else {
			Console::println("Failed to allocate memory for the new background music: "
			                 + key);
			Console::printTrace();
		}

		return result;
	}

	void SDLMixerEngine::askForDisconnect() {
		disconnect = true;
	}

	void SDLMixerEngine::setMusicVolume(int newMusicVolume) {
		this->MusicEngine::setMusicVolume(newMusicVolume);

		if (!this->MusicEngine::isMuted()) {
			if (SDLMixerBackgroundMusic::currentMusic) {
				Mix_VolumeMusic(SDLMixerEngine::baconBoxToSdlVolume(static_cast<int>(static_cast<float>(SDLMixerBackgroundMusic::currentMusic->getVolume()) * static_cast<float>(getMusicVolume()) / static_cast<float>(Sound::MAX_VOLUME))));
			}
		}
	}

	void SDLMixerEngine::setSoundVolume(int newSoundVolume) {
		this->SoundEngine::setSoundVolume(newSoundVolume);

		if (!this->SoundEngine::isMuted()) {
			soundVolumeChange();
		}
	}

	SDLMixerEngine::SDLMixerEngine() : SoundEngine(), MusicEngine(),
		disconnect(false) {
		instance = this;
		lastFadeTick = SDL_GetTicks();
		lastFadeTick -= lastFadeTick % NB_TICKS_PER_FADE;

		// We initialize SDL_mixer.
		if (!Mix_OpenAudio(SDLMixerEngine::AUDIO_RATE, SDLMixerEngine::AUDIO_FORMAT, SDLMixerEngine::AUDIO_CHANNELS, SDLMixerEngine::AUDIO_BUFFERS)) {
			// We set the function to call when a music is stopped.
			Mix_HookMusicFinished(SDLMixerBackgroundMusic::stoppedCurrentMusic);
			// We set the function to call when a sound effect is stopped.
			Mix_ChannelFinished(SDLMixerSoundFX::channelHalted);
			// We set the number of sound effect channels.
			Mix_AllocateChannels(SDLMixerEngine::NB_SOUND_CHANNELS);

		} else {
			Console::println("Unable to initialize audio: " + std::string(Mix_GetError()));
			Console::printTrace();
		}
	}

	SDLMixerEngine::~SDLMixerEngine() {
		Mix_CloseAudio();
		instance = NULL;
	}

	void SDLMixerEngine::update() {
		// We update the pause/resume fading.
		if (SDL_GetTicks() > lastFadeTick + NB_TICKS_PER_FADE) {
			lastFadeTick += NB_TICKS_PER_FADE;
			fadeUpdate.shoot(lastFadeTick);

			if (disconnect) {
				fadeUpdate.disconnectAll();
			}
		}

		// For each sound (music or sound effect).
		std::list<Sound *>::iterator i = sounds.begin();

		while (i != sounds.end()) {
			// We make sure the pointer is valid.
			if (*i) {
				if ((*i)->getCurrentState() == AudioState::STOPPED) {
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

	SoundInfo *SDLMixerEngine::loadSound(const std::string &filePath) {
		SoundInfo *result = new SoundInfo();
		result->data = Mix_LoadWAV(filePath.c_str());

		// We make sure the sound file is correctly loaded.
		if (!result->data) {
			// We delete the resulting sound info.
			delete result;
			result = NULL;
			Console::println("Unable to load sound effect: " + filePath);
			Console::println(" with SDL_mixer error: " + std::string(Mix_GetError()));
			Console::printTrace();
		}

		return result;
	}

	SoundInfo *SDLMixerEngine::loadSound(const SoundParameters &params) {
		return loadSound(params.path);
	}

	bool SDLMixerEngine::unloadSound(SoundInfo *sound) {
		if (sound && sound->data) {
			Mix_FreeChunk(sound->data);
		}

		return true;
	}

	MusicInfo *SDLMixerEngine::loadMusic(const std::string &filePath) {
		MusicInfo *result = new MusicInfo();

		if (result) {
			result->music = Mix_LoadMUS(filePath.c_str());

			if (!result->music) {
				delete result;
				result = NULL;
				Console::println("Unable to load music file: " + filePath);
				Console::println(" with the SDL_mixer error: " + std::string(Mix_GetError()));
				Console::printTrace();
			}

		} else {
			Console::println("Could not allocate memory for the music info for the file: "
			                 + filePath);
			Console::printTrace();
		}

		return result;
	}

	MusicInfo *SDLMixerEngine::loadMusic(const MusicParameters &params) {
		return loadMusic(params.filePath);
	}

	bool SDLMixerEngine::unloadMusic(MusicInfo *music) {
		if (music && music->music) {
			Mix_FreeMusic(music->music);
		}

		return true;
	}
}

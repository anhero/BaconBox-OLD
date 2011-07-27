#include "SDLMixerBackgroundMusic.h"

#include <SDL/SDL.h>

#include "Console.h"

#include "SDLMixerEngine.h"

using namespace RedBox;

SDLMixerBackgroundMusic* SDLMixerBackgroundMusic::currentMusic = NULL;
bool SDLMixerBackgroundMusic::isBeingPaused = false;

void SDLMixerBackgroundMusic::stoppedCurrentMusic() {
	if(!isBeingPaused) {
		currentMusic = NULL;
	} else {
		isBeingPaused = false;
	}
}

void SDLMixerBackgroundMusic::setSDLMusicVolume(int newRedBoxVolume) {
	Mix_VolumeMusic(SDLMixerEngine::redBoxToSdlVolume(static_cast<int>(static_cast<float>(newRedBoxVolume) * static_cast<float>(AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(Sound::MAX_VOLUME))));
}

void SDLMixerBackgroundMusic::setSDLMusicVolumeNoConvert(int newSDLVolume) {
	Mix_VolumeMusic(static_cast<int>(static_cast<float>(newSDLVolume) * static_cast<float>(SDLMixerEngine::redBoxToSdlVolume(AudioEngine::getMusicEngine().getMusicVolume())) / static_cast<float>(SDLMixerEngine::redBoxToSdlVolume(Sound::MAX_VOLUME))));
}


SDLMixerBackgroundMusic::~SDLMixerBackgroundMusic() {
}

void SDLMixerBackgroundMusic::play(int nbTimes) {
	if(music) {
		resetPauseResumeFade();
		Mix_HaltMusic();

		if(!Mix_PlayMusic(music, nbTimes)) {
			setSDLMusicVolume(getVolume());
			currentMusic = this;
			looping = (nbTimes == -1);
			neverPlayed = false;
		} else {
			Console::print("Error playing a music with Mix_PlayMusic(): " + std::string(Mix_GetError()));
			Console::printTrace();
		}
	}
}

void SDLMixerBackgroundMusic::stop() {
	if(music && currentMusic == this) {
		resetPauseResumeFade();
		Mix_HaltMusic();
		currentMusic = NULL;
	}
}

void SDLMixerBackgroundMusic::pause() {
	if(music && currentMusic == this) {
		resetPauseResumeFade();
		Mix_PauseMusic();
	}
}

void SDLMixerBackgroundMusic::resume() {
	if(music) {
		resetPauseResumeFade();
		setSDLMusicVolume(getVolume());
		Mix_ResumeMusic();
	}
}

bool SDLMixerBackgroundMusic::isLooping() {
	return looping && currentMusic == this && Mix_PlayingMusic();
}

void SDLMixerBackgroundMusic::setVolume(int newVolume) {
	this->Sound::setVolume(newVolume);
	AudioState currentState = getCurrentState();
	if(currentState == AudioState::PLAYING ||
			currentState == AudioState::FADING_IN ||
			currentState == AudioState::FADING_OUT) {
		setSDLMusicVolume(getVolume());
	}
}

AudioState SDLMixerBackgroundMusic::getCurrentState() const {
	if(neverPlayed || !music) {
		return AudioState::INITIAL;
	} else if(currentMusic == this && Mix_PlayingMusic()) {
		switch(Mix_FadingMusic()) {
		case MIX_NO_FADING:
			return AudioState::PLAYING;
			break;
		case MIX_FADING_OUT:
			return AudioState::FADING_OUT;
			break;
		case MIX_FADING_IN:
			return AudioState::FADING_IN;
			break;
		default:
			break;
		}
	} else if(currentMusic == this && Mix_PausedMusic()) {
		return AudioState::PAUSED;
	}

	return AudioState::STOPPED;
}

void SDLMixerBackgroundMusic::play(int nbTimes, double fadeIn) {
	if(music) {
		resetPauseResumeFade();
		Mix_HaltMusic();

		if(!Mix_FadeInMusic(music, nbTimes, static_cast<int>(fadeIn * 1000.0))) {
			setSDLMusicVolume(getVolume());
			currentMusic = this;
			looping = (nbTimes == -1);
			neverPlayed = false;
		} else {
			Console::print("Error playing a music with Mix_FadeInMusic(): " + std::string(Mix_GetError()));
			Console::printTrace();
		}
	}
}

void SDLMixerBackgroundMusic::stop(double fadeOut) {
	if(music && currentMusic == this) {
		resetPauseResumeFade();
		Mix_FadeOutMusic(static_cast<int>(fadeOut * 1000.0));
	}
}

void SDLMixerBackgroundMusic::pause(double fadeOut) {
	if(music && currentMusic == this) {
		pauseResumeFading = true;
		fadeTime = static_cast<unsigned int>(fadeOut * 1000.0);
		fadeStart = SDL_GetTicks();
		fadeType = FADE_OUT;
		SDLMixerEngine::getInstance().fadeUpdate.connect(this, &SDLMixerBackgroundMusic::fadeUpdate);
	}
}

void SDLMixerBackgroundMusic::resume(double fadeIn) {
	if(music && currentMusic == this) {
		pauseResumeFading = true;
		fadeTime = static_cast<unsigned int>(fadeIn * 1000.0);
		fadeStart = SDL_GetTicks();
		fadeType = FADE_IN;
		SDLMixerEngine::getInstance().fadeUpdate.connect(this, &SDLMixerBackgroundMusic::fadeUpdate);
		setSDLMusicVolume(0);
		Mix_ResumeMusic();
	}
}

SDLMixerBackgroundMusic::SDLMixerBackgroundMusic() : BackgroundMusic(),
	music(NULL), looping(false), neverPlayed(true), pauseResumeFading(false), fadeTime(0),
	fadeStart(0) {
}

void SDLMixerBackgroundMusic::load(Mix_Music* newMusic) {
	music = newMusic;
}

void SDLMixerBackgroundMusic::fadeUpdate(unsigned int ticks) {
	if(pauseResumeFading) {
		if(ticks > fadeStart) {
			int newVolume = 0;

			// If the fading is over.
			if(ticks - fadeStart > fadeTime) {
				if(fadeType == FADE_IN) {
					newVolume = SDLMixerEngine::redBoxToSdlVolume(getVolume());
				}

				pauseResumeFading = false;
				fadeTime = 0;
				fadeStart = 0;
			} else {
				// If we are fading in.
				if(fadeType == FADE_IN) {
					newVolume = static_cast<int>(static_cast<double>(ticks - fadeStart) / static_cast<double>(fadeTime) * static_cast<double>(SDLMixerEngine::redBoxToSdlVolume(getVolume())));
				} else {
					// If we are fading out.
					newVolume = SDLMixerEngine::redBoxToSdlVolume(getVolume()) - static_cast<int>(static_cast<double>(ticks - fadeStart) / static_cast<double>(fadeTime) * static_cast<double>(SDLMixerEngine::redBoxToSdlVolume(getVolume())));
				}
			}

			if(newVolume) {
				setSDLMusicVolumeNoConvert(newVolume);
			} else {
				pause();
				setSDLMusicVolume(getVolume());
			}
		}
	} else {
		SDLMixerEngine::getInstance().askForDisconnect();
	}
}

void SDLMixerBackgroundMusic::resetPauseResumeFade() {
	pauseResumeFading = false;
	fadeTime = 0;
	fadeStart = 0;
	setSDLMusicVolume(getVolume());
}

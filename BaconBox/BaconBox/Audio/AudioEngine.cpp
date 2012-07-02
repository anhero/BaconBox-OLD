#include "BaconBox/Audio/AudioEngine.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/Audio/SoundFX.h"
#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Engine.h"

namespace BaconBox {
	SoundEngine &AudioEngine::getSoundEngine() {
		return Engine::getSoundEngine();
	}

	MusicEngine &AudioEngine::getMusicEngine() {
		return Engine::getMusicEngine();
	}

	void AudioEngine::playSoundFX(const std::string &key, int nbTimes) {
		SoundFX *sound = getSoundEngine().getSoundFX(key, false);

		if (sound) {
			sound->play(nbTimes);
		}
	}

	void AudioEngine::playBackgroundMusic(const std::string &key, int nbTimes,
	                                      double fadeIn) {
		BackgroundMusic *music = getMusicEngine().getBackgroundMusic(key, false);

		if (music) {
			if (fadeIn) {
				music->play(nbTimes, fadeIn);

			} else {
				music->play(nbTimes);
			}
		}
	}

	AudioEngine::AudioEngine() {
	}

	AudioEngine::~AudioEngine() {
	}
}

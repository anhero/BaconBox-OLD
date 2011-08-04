#include "AudioEngine.h"

#include "PlatformFlagger.h"

#include "SoundEngine.h"
#include "MusicEngine.h"
#include "SoundFX.h"
#include "BackgroundMusic.h"

#ifdef RB_SOUND_ENGINE_INCLUDE
#include RB_SOUND_ENGINE_INCLUDE
#endif
#ifdef RB_MUSIC_ENGINE_INCLUDE
#include RB_MUSIC_ENGINE_INCLUDE
#endif

using namespace RedBox;

SoundEngine& AudioEngine::getSoundEngine() {
	return RB_SOUND_ENGINE;
}

MusicEngine& AudioEngine::getMusicEngine() {
	return RB_MUSIC_ENGINE;
}

void AudioEngine::playSoundFX(const std::string &key, int nbTimes) {
	SoundFX* sound = getSoundEngine().getSoundFX(key, false);
	if(sound) {
		sound->play(nbTimes);
	}
}

void AudioEngine::playBackgroundMusic(const std::string &key, int nbTimes,
									  double fadeIn) {
	BackgroundMusic* music = getMusicEngine().getBackgroundMusic(key, false);
	if(music) {
		if(fadeIn) {
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

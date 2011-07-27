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

SoundEngine* AudioEngine::soundEngine = NULL;
MusicEngine* AudioEngine::musicEngine = NULL;

void AudioEngine::loadAudioEngine() {
	loadSoundEngine();
	loadMusicEngine();
}

void AudioEngine::loadSoundEngine() {
	if(soundEngine == NULL) {
		soundEngine = RB_SOUND_ENGINE;
		if(soundEngine) {
			soundEngine->init();
		}
	}
}

void AudioEngine::loadMusicEngine() {
	if(musicEngine == NULL) {
		musicEngine = RB_MUSIC_ENGINE;
		if(musicEngine) {
			musicEngine->init();
		}
	}
}

SoundEngine* AudioEngine::getSoundEngine() {
	if(!soundEngine) {
		loadSoundEngine();
	}
	return soundEngine;
}

MusicEngine* AudioEngine::getMusicEngine() {
	if(!musicEngine) {
		loadMusicEngine();
	}
	return musicEngine;
}

void AudioEngine::playSoundFX(const std::string &key, int nbTimes) {
	SoundEngine* engine = getSoundEngine();
	if(engine) {
		SoundFX* sound = engine->getSoundFX(key, false);
		if(sound) {
			sound->play(nbTimes);
		}
	}
}

void AudioEngine::playBackgroundMusic(const std::string &key, int nbTimes,
									  double fadeIn) {
	MusicEngine* engine = getMusicEngine();
	if(engine) {
		BackgroundMusic* music = engine->getBackgroundMusic(key, false);
		if(music) {
			if(fadeIn) {
				music->play(nbTimes, fadeIn);
			} else {
				music->play(nbTimes);
			}
		}
	}
}

AudioEngine::AudioEngine() {
}

AudioEngine::~AudioEngine() {
}

void AudioEngine::unloadAudioEngines() {
	if(soundEngine) {
		delete soundEngine;
		soundEngine = NULL;
	}
	if(musicEngine) {
		delete musicEngine;
		musicEngine = NULL;
	}
}


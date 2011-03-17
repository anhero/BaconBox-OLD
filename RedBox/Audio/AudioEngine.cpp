#include "AudioEngine.h"

#include "PlatformFlagger.h"

#include "SoundEngine.h"
#include "MusicEngine.h"

#ifdef RB_SOUND_ENGINE_INCLUDE
#include RB_SOUND_ENGINE_INCLUDE
#endif
#ifdef RB_MUSIC_ENGINE_INCLUDE
#include RB_MUSIC_ENGINE_INCLUDE
#endif

#include "Debug.h"

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


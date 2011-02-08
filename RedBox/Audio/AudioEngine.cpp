#include "AudioEngine.h"

#include "PlatformFlagger.h"

#ifdef RB_SOUND_ENGINE_INCLUDE
#include RB_SOUND_ENGINE_INCLUDE
#endif
#ifdef RB_MUSIC_ENGINE_INCLUDE
#include RB_MUSIC_ENGINE_INCLUDE
#endif

#include "Debug.h"

using namespace RedBox;

AudioEngine* AudioEngine::soundEngine = NULL;
AudioEngine* AudioEngine::musicEngine = NULL;

void AudioEngine::loadAudioEngine() {
	loadSoundEngine();
	loadMusicEngine();
}
void AudioEngine::loadSoundEngine() {
	if(soundEngine == NULL) {
		soundEngine = RB_SOUND_ENGINE;
	}
}
void AudioEngine::loadMusicEngine() {
	if(musicEngine == NULL) {
		musicEngine = RB_MUSIC_ENGINE;
	}
}
AudioEngine* AudioEngine::getSoundEngine() {
	if(!soundEngine) {
		loadSoundEngine();
	}
	return soundEngine;
}
AudioEngine* AudioEngine::getMusicEngine() {
	if(!musicEngine) {
		loadMusicEngine();
	}
	return musicEngine;
}

AudioEngine::AudioEngine() {
}
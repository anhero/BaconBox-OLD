#include "MusicEngine.h"
#include "BackgroundMusic.h"
#include "MusicInfo.h"

using namespace RedBox;

int MusicEngine::getMusicVolume() const {
	return musicVolume;
}

void MusicEngine::setMusicVolume(int newMusicVolume) {
	musicVolume = (newMusicVolume < Sound::MIN_VOLUME) ? (Sound::MIN_VOLUME) : ((newMusicVolume > Sound::MAX_VOLUME) ? (Sound::MAX_VOLUME) : (newMusicVolume));
}

MusicEngine::MusicEngine(): AudioEngine(), musicVolume(Sound::MAX_VOLUME) {
}

MusicEngine::~MusicEngine() {
}

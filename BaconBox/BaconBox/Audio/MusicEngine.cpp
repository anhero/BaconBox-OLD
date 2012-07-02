#include "BaconBox/Audio/MusicEngine.h"
#include "BaconBox/Audio/BackgroundMusic.h"
#include "BaconBox/Audio/MusicInfo.h"

using namespace BaconBox;

int MusicEngine::getMusicVolume() const {
	if(isMuted()) {
		return muteValue;
	} else {
		return musicVolume;
	}
}

void MusicEngine::setMusicVolume(int newMusicVolume) {
	if(isMuted()) {
		muteValue = (newMusicVolume < Sound::MIN_VOLUME) ? (Sound::MIN_VOLUME) : ((newMusicVolume > Sound::MAX_VOLUME) ? (Sound::MAX_VOLUME) : (newMusicVolume));
	} else {
		musicVolume = (newMusicVolume < Sound::MIN_VOLUME) ? (Sound::MIN_VOLUME) : ((newMusicVolume > Sound::MAX_VOLUME) ? (Sound::MAX_VOLUME) : (newMusicVolume));
	}
}

bool MusicEngine::isMuted() const {
	return muteValue != -1;
}

void MusicEngine::setMuted(bool newMuted) {
	if(!isMuted() && newMuted) {
		int tmp = getMusicVolume();
		setMusicVolume(Sound::MIN_VOLUME);
		muteValue = tmp;
	} else if(isMuted() && !newMuted) {
		musicVolume = muteValue;
		muteValue = -1;
		setMusicVolume(musicVolume);
	}
}

void MusicEngine::mute() {
	setMuted(true);
}

void MusicEngine::unmute() {
	setMuted(false);
}

MusicEngine::MusicEngine(): AudioEngine(), musicVolume(Sound::MAX_VOLUME),
	muteValue(-1) {
}

MusicEngine::~MusicEngine() {
}

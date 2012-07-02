#include "BaconBox/Audio/SoundEngine.h"
#include "BaconBox/Audio/SoundFX.h"
#include "BaconBox/Audio/SoundInfo.h"

using namespace BaconBox;

int SoundEngine::getSoundVolume() const {
	if(isMuted()) {
		return muteValue;
	} else {
		return soundVolume;
	}
}

void SoundEngine::setSoundVolume(int newSoundVolume) {
	if(isMuted()) {
		muteValue = (newSoundVolume < Sound::MIN_VOLUME) ? (Sound::MIN_VOLUME) : ((newSoundVolume > Sound::MAX_VOLUME) ? (Sound::MAX_VOLUME) : (newSoundVolume));
	} else {
		soundVolume = (newSoundVolume < Sound::MIN_VOLUME) ? (Sound::MIN_VOLUME) : ((newSoundVolume > Sound::MAX_VOLUME) ? (Sound::MAX_VOLUME) : (newSoundVolume));
	}
}

bool SoundEngine::isMuted() const {
	return muteValue != -1;
}

void SoundEngine::setMuted(bool newMuted) {
	if(!isMuted() && newMuted) {
		int tmp = getSoundVolume();
		setSoundVolume(Sound::MIN_VOLUME);
		muteValue = tmp;
	} else if(isMuted() && !newMuted) {
		soundVolume = muteValue;
		muteValue = -1;
		setSoundVolume(soundVolume);
	}
}

void SoundEngine::mute() {
	setMuted(true);
}

void SoundEngine::unmute() {
	setMuted(false);
}

SoundEngine::SoundEngine(): AudioEngine(), soundVolume(Sound::MAX_VOLUME),
	muteValue(-1) {
}

SoundEngine::~SoundEngine() {
}

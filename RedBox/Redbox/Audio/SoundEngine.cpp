#include "SoundEngine.h"
#include "SoundFX.h"
#include "SoundInfo.h"

using namespace RedBox;

int SoundEngine::getSoundVolume() const {
	return soundVolume;
}

void SoundEngine::setSoundVolume(int newSoundVolume) {
	soundVolume = (newSoundVolume < Sound::MIN_VOLUME) ? (Sound::MIN_VOLUME) : ((newSoundVolume > Sound::MAX_VOLUME) ? (Sound::MAX_VOLUME) : (newSoundVolume));
}

SoundEngine::SoundEngine(): AudioEngine(), soundVolume(Sound::MAX_VOLUME) {
}

SoundEngine::~SoundEngine() {
}

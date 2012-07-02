#include "BaconBox/Audio/Sound.h"

using namespace BaconBox;

Sound::~Sound() {
}

int Sound::getVolume() const {
	return volume;
}

void Sound::setVolume(int newVolume) {
	volume = (newVolume < MIN_VOLUME) ? (MIN_VOLUME) : ((newVolume > MAX_VOLUME) ? (MAX_VOLUME) : (newVolume));
}

Sound::Sound() : volume(MAX_VOLUME) {
}

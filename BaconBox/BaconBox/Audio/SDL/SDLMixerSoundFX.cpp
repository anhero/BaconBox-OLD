#include "BaconBox/Audio/SDL/SDLMixerSoundFX.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Audio/SDL/SDLMixerEngine.h"

using namespace BaconBox;

sigly::Signal1<int> SDLMixerSoundFX::haltChannel = sigly::Signal1<int>();

void SDLMixerSoundFX::channelHalted(int channel) {
	haltChannel(channel);
}

void SDLMixerSoundFX::play(int nbTimes) {
	if(data && nbTimes != 0 && nbTimes >= LOOPING) {
		hasPlayed = true;
		looping = nbTimes == LOOPING;
		nbTimes -= ((looping) ? (0) : (1));
		channel = Mix_PlayChannel(-1, data, nbTimes);
		refreshVolume(getVolume());
	}
}

void SDLMixerSoundFX::stop() {
	if(data && channel > INVALID_CHANNEL) {
		Mix_HaltChannel(channel);
		channel = INVALID_CHANNEL;
		looping = false;
	}
}

void SDLMixerSoundFX::pause() {
	if(data && channel > INVALID_CHANNEL) {
		Mix_Pause(channel);
	}
}

void SDLMixerSoundFX::resume() {
	if(data && channel > INVALID_CHANNEL) {
		Mix_Resume(channel);
	}
}

bool SDLMixerSoundFX::isLooping() {
	// We make sure that the channel is looping AND that it is not paused.
	return looping && channel && Mix_Playing(channel);
}

void SDLMixerSoundFX::setVolume(int newVolume) {
	this->Sound::setVolume(newVolume);
	refreshVolume(getVolume());
}

AudioState SDLMixerSoundFX::getCurrentState() const {
	AudioState result = AudioState::INITIAL;

	if(hasPlayed) {
		if(channel == INVALID_CHANNEL) {
			result = AudioState::STOPPED;
		} else {
			if(Mix_Playing(channel)) {
				result = AudioState::PLAYING;
			} else {
				result = AudioState::PAUSED;
			}
		}
	}

	return result;
}

SDLMixerSoundFX::~SDLMixerSoundFX() {
}

SDLMixerSoundFX::SDLMixerSoundFX() : SoundFX(), looping(false), channel(-1),
	data(NULL), hasPlayed(false) {
	haltChannel.connect(this, &SDLMixerSoundFX::onChannelHalt);
	SDLMixerEngine::getInstance()->soundVolumeChange.connect(this, &SDLMixerSoundFX::soundVolumeChanged);
}

void SDLMixerSoundFX::load(Mix_Chunk* newData) {
	data = newData;
}

int SDLMixerSoundFX::getChannel() const {
	return channel;
}

void SDLMixerSoundFX::onChannelHalt(int channelHalted) {
	// We take note if our channel is stopped.
	if(channelHalted == channel) {
		channel = INVALID_CHANNEL;
	}
}

void SDLMixerSoundFX::soundVolumeChanged() {
	refreshVolume(getVolume());
}

void SDLMixerSoundFX::refreshVolume(int newVolume) {
	if(channel != INVALID_CHANNEL) {
		Mix_Volume(channel, SDLMixerEngine::baconBoxToSdlVolume(static_cast<int>(static_cast<float>(newVolume) * (static_cast<float>(SDLMixerEngine::getInstance()->getSoundVolume()) / static_cast<float>(Sound::MAX_VOLUME)))));
	}
}

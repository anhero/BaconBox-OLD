#include "BaconBox/Audio/OpenAL/OpenALSoundFX.h"

#include "BaconBox/PlatformFlagger.h"

#include <cassert>

#include "BaconBox/Console.h"
#include "BaconBox/Audio/OpenAL/OpenALEngine.h"

using namespace BaconBox;

void OpenALSoundFX::play(int nbTimes) {
	if(nbTimes == 0) {
		nbTimesLeft = 0;
	} else {
		// We take care to set the looping.
		if(nbTimes < 0) {
			alSourcei(sourceId, AL_LOOPING, 1);
		} else {
			nbTimesLeft = nbTimes - 1;
		}

		ALint state;
		alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

		if(state != AL_PAUSED) {
			alSourceRewind(sourceId);
		}

		alSourcef(sourceId, AL_GAIN, OpenALEngine::baconBoxToOpenALVolume(getVolume()));
		// We start playing the sound.
		alSourcePlay(sourceId);
	}
}

void OpenALSoundFX::stop() {
	alSourceStop(sourceId);
}

void OpenALSoundFX::pause() {
	alSourcePause(sourceId);
}

void OpenALSoundFX::resume() {
	ALint state;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

	// We only want to resume if the sound was actually paused.
	if(state == AL_PAUSED) {
		alSourcePlay(sourceId);
	}
}

bool OpenALSoundFX::isLooping() {
	ALint looping;
	alGetSourcei(sourceId, AL_LOOPING, &looping);
	return static_cast<bool>(looping);
}

void OpenALSoundFX::setVolume(int newVolume) {
	this->Sound::setVolume(newVolume);
	alSourcef(sourceId, AL_GAIN, OpenALEngine::baconBoxToOpenALVolume(newVolume));
}

AudioState OpenALSoundFX::getCurrentState() const {
	ALint state;
	AudioState result = AudioState::INITIAL;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

	switch(state) {
	case AL_INITIAL:
		result = AudioState::INITIAL;
		break;
	case AL_PLAYING:
		result = AudioState::PLAYING;
		break;
	case AL_PAUSED:
		result = AudioState::PAUSED;
		break;
	default:
		result = AudioState::STOPPED;
		break;
	}

	return result;
}

OpenALSoundFX::~OpenALSoundFX() {
	alDeleteSources(1, &sourceId);
}

ALuint& OpenALSoundFX::getSourceId() {
    return sourceId;
}

OpenALSoundFX::OpenALSoundFX(): SoundFX(), sourceId(0), survives(false),
	nbTimesLeft(0) {
}

void OpenALSoundFX::load(ALuint bufferId) {
	alGenSources(1, &sourceId);
	alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sourceId, AL_BUFFER, bufferId);
}

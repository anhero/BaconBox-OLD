#include "OpenALSoundFX.h"

#include "OpenALEngine.h"

#include <cassert>

#include "Debug.h"

using namespace RedBox;

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
	alSourcePlay(sourceId);
}

OpenALSoundFX::OpenALSoundFX(): SoundFX(), sourceId(0), survives(false), 
nbTimesLeft(0){
}

OpenALSoundFX::~OpenALSoundFX() {
	alDeleteSources(1, &sourceId);
}

void OpenALSoundFX::load(ALuint bufferId) {
	assert(OpenALEngine::getInstance());
	alGenSources(1, &sourceId);
	alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sourceId, AL_BUFFER, bufferId);
}


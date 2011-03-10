#include "OpenALSoundFX.h"

#include "OpenALEngine.h"

#include <cassert>

using namespace RedBox;

void OpenALSoundFX::play(int nbTimes) {
	ALint bufferId;
	if(nbTimes != 0) {
		// We make sure the OpenALEngine is initialized.
		assert(OpenALEngine::getInstance());
		// We take care to set the looping.
		if(nbTimes > 1) {
			// We generate a queue of buffer id's to loop.
			ALuint* queue = new ALuint[nbTimes];
			for(int i = nbTimes - 1; i >= 0; --i) {
				alGetSourcei(sourceId, AL_BUFFER, &bufferId);
				queue[i] = static_cast<ALuint>(bufferId);
			}
			alSourceQueueBuffers(sourceId, static_cast<ALsizei>(nbTimes), queue);
			delete[] queue;
		// If infinite looping was specified.
		} else if(nbTimes < 0) {
			alSourcei(sourceId, AL_LOOPING, 1);
		} else {
			alSourcei(sourceId, AL_LOOPING, 0);
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

OpenALSoundFX::OpenALSoundFX(): SoundFX(), sourceId(0), survives(false) {
}

OpenALSoundFX::~OpenALSoundFX() {
	alDeleteSources(1, &sourceId);
}

void OpenALSoundFX::load(ALuint bufferId, char* bufferData) {
	assert(OpenALEngine::getInstance());
	alGenSources(1, &sourceId);
	alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sourceId, AL_BUFFER, bufferId);
}


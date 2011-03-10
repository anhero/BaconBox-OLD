#include "OpenALSoundFX.h"

#include "OpenALEngine.h"

#include <cassert>

using namespace RedBox;

void OpenALSoundFX::play(int nbTimes) {
	if(nbTimes != 0) {
		// We make sure the OpenALEngine is initialized.
		assert(OpenALEngine::getInstance());
		ALuint source;
		alGenSources(1, &source);
		alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);
		// We take care to set the looping.
		if(nbTimes > 1) {
			// We generate a queue of buffer id's to loop.
			ALuint* queue = new ALuint[nbTimes];
			for(int i = nbTimes - 1; i >= 0; --i) {
				queue[i] = bufferId;
			}
			alSourceQueueBuffers(source, static_cast<ALsizei>(nbTimes), queue);
			delete[] queue;
		} else {
			// If infinite looping was specified.
			if(nbTimes < 0) {
				alSourcei(source, AL_LOOPING, 1);
			}
			// We set the buffer for the source.
			alSourcei(source, AL_BUFFER, bufferId);
		}
		// We start playing the sound.
		alSourcePlay(source);
		// We add the source to the OpenALEngine.
		OpenALEngine::getInstance()->addSource(source);
	}
}

bool OpenALSoundFX::getSurvives() const {
	return survives;
}

void OpenALSoundFX::setSurvives(bool newSurvives) {
	survives = newSurvives;
}

ALuint& OpenALSoundFX::getSourceId() {
	return sourceId;
}

OpenALSoundFX::OpenALSoundFX(): SoundFX(), sourceId(0), survives(false) {
}

OpenALSoundFX::~OpenALSoundFX() {
}

void OpenALSoundFX::load(ALuint bufferId, char* bufferData) {
	assert(OpenALEngine::getInstance());
	alGenSources(1, &sourceId);
	alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sourceId, AL_BUFFER, bufferId);
}


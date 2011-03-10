#include "OpenALSoundFX.h"

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

OpenALSoundFX::OpenALSoundFX(): SoundFX(), bufferId(0), bufferData(NULL) {
}

OpenALSoundFX::~OpenALSoundFX() {
	assert(OpenALEngine::getInstance());
	// We delete the buffer's sources still playing, else we can't delete the
	// buffer.
	OpenALEngine::getInstance()->deleteBufferSources(bufferId);
	// We delete the buffer from OpenAL.
	alDeleteBuffers(1, &bufferId);
	if(bufferData) {
		delete[] bufferData;
	}
}

bool OpenALSoundFX::load(const std::string& filePath) {
	assert(OpenALEngine::getInstance());
	ALenum format;
	ALsizei bufferSize, freq;
	OpenALEngine::loadWav(filePath, bufferData, bufferSize, format, freq);
	// We check that the buffer was loaded correctly.
	if(bufferData) {
		alGenBuffers(1, &bufferId);
		alBufferData(bufferId, format, bufferData, bufferSize, freq);
		return true;
	} else {
		return false;
	}
}


#include "BaconBox/Audio/ios/RBAudioPlayerMusic.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Console.h"
#include <cassert>

using namespace BaconBox;

RBAudioPlayerMusic* RBAudioPlayerMusic::currentMusic = NULL;

void RBAudioPlayerMusic::play(int nbTimes) {
	play(nbTimes, 0.0);
}

void RBAudioPlayerMusic::play(int nbTimes, double fadeIn) {
	assert(bgm);
	if(nbTimes != 0) {
		if (nbTimes > 0) {
			--nbTimes;
		}
		if(fadeIn >= 0.0) {
			[bgm fadeInPlay:nbTimes :static_cast<float>(fadeIn)];
			playedOnce = true;
			currentMusic = this;
		} else {
			Console::print("Tried to play a music with an invalid fade in time : " +
				Console::toString(fadeIn) + " sec.");
		}
	}
}

void RBAudioPlayerMusic::stop() {
	stop(0.0);
}

void RBAudioPlayerMusic::stop(double fadeOut) {
	assert(bgm);
	if(fadeOut >= 0.0) {
		[bgm fadeOutStop:static_cast<float>(fadeOut)];
		currentMusic = NULL;
	} else {
		Console::print("Tried to stop a music with an invalid fade out time : " +
			  Console::toString(fadeOut) + " sec.");
	}
}

void RBAudioPlayerMusic::pause() {
	pause(0.0);
}

void RBAudioPlayerMusic::pause(double fadeOut) {
	assert(bgm);
	if(fadeOut >= 0.0) {
		[bgm fadeOutPause:static_cast<float>(fadeOut)];
	} else {
		Console::print("Tried to pause a music with an invalid fade out time : " +
			  Console::toString(fadeOut) + " sec.");
	}
}

void RBAudioPlayerMusic::resume() {
	resume(0.0);
}

void RBAudioPlayerMusic::resume(double fadeIn) {
	assert(bgm);
	if(fadeIn >= 0.0) {
		[bgm fadeInResume:static_cast<float>(fadeIn)];
		playedOnce = true;
	} else {
		Console::print("Tried to resume a music with an invalid fade in time : " +
			  Console::toString(fadeIn) + " sec.");
	}
}

bool RBAudioPlayerMusic::isLooping() {
	return [bgm isLooping];
}

void RBAudioPlayerMusic::setVolume(int newVolume) {
	this->Sound::setVolume(newVolume);
	[bgm setVolume:(static_cast<float>(getVolume()) / static_cast<float>(Sound::MAX_VOLUME))];
}

AudioState RBAudioPlayerMusic::getCurrentState() const {
	if(!playedOnce) {
		return AudioState::INITIAL;
	} else if([bgm isStopped]) {
		return AudioState::STOPPED;
	} else if([bgm isPaused]) {
		return AudioState::PAUSED;
	} else {
		return AudioState::PLAYING;
	}
}

RBAudioPlayerMusic::~RBAudioPlayerMusic() {
}

void RBAudioPlayerMusic::refreshVolume() {
	if(currentMusic) {
		[currentMusic->bgm refreshVolume];
	}
}

RBAudioPlayerMusic::RBAudioPlayerMusic(): BackgroundMusic(), bgm(NULL),
playedOnce(false) {
}

void RBAudioPlayerMusic::load(std::string const& filePath) {
	if(!bgm) {
		const char* tmp = filePath.c_str();
		bgm = [[RBAudioPlayerMusicDelegate alloc] initWithPath:[NSString stringWithCString:tmp]];
	}
}

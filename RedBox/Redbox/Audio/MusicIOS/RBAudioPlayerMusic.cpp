#include "RBAudioPlayerMusic.h"

#include "Debug.h"
#include <cassert>

using namespace RedBox;

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
		} else {
			RB_ECHO("Tried to play a music with an invalid fade in time : " <<
				  fadeIn << " sec.");
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
	} else {
		RB_ECHO("Tried to stop a music with an invalid fade out time : " <<
			  fadeOut << " sec.");
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
		RB_ECHO("Tried to pause a music with an invalid fade out time : " <<
			  fadeOut << " sec.");
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
		RB_ECHO("Tried to resume a music with an invalid fade in time : " <<
			  fadeIn << " sec.");
	}
}

bool RBAudioPlayerMusic::isLooping() {
	return [bgm isLooping];
}

AudioState::Enum RBAudioPlayerMusic::getCurrentState() const {
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

RBAudioPlayerMusic::RBAudioPlayerMusic(): BackgroundMusic(), bgm(NULL),
playedOnce(false) {
}

void RBAudioPlayerMusic::load(std::string const& filePath) {
	if(!bgm) {
		const char* tmp = filePath.c_str();
		bgm = [[RBAudioPlayerMusicDelegate alloc] initWithPath:[NSString stringWithCString:tmp]];
	}
}
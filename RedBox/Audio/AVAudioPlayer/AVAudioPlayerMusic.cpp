#include "AVAudioPlayerMusic.h"

#include "Debug.h"
#include <cassert>

using namespace RedBox;

void AVAudioPlayerMusic::play(int nbTimes) {
	play(nbTimes, 0.0);
}

void AVAudioPlayerMusic::play(int nbTimes, double fadeIn) {
	assert(bgm);
	if(nbTimes != 0) {
		if (nbTimes > 0) {
			--nbTimes;
		}
		if(fadeIn >= 0.0) {
			[bgm fadeInPlay:nbTimes :static_cast<float>(fadeIn)];
			playedOnce = true;
		} else {
			$ECHO("Tried to play a music with an invalid fade in time : " <<
				  fadeIn << " sec.");
		}
	}
}

void AVAudioPlayerMusic::stop() {
	stop(0.0);
}

void AVAudioPlayerMusic::stop(double fadeOut) {
	assert(bgm);
	if(fadeOut >= 0.0) {
		[bgm fadeOutStop:static_cast<float>(fadeOut)];
	} else {
		$ECHO("Tried to stop a music with an invalid fade out time : " <<
			  fadeOut << " sec.");
	}
}

void AVAudioPlayerMusic::pause() {
	pause(0.0);
}

void AVAudioPlayerMusic::pause(double fadeOut) {
	assert(bgm);
	if(fadeOut >= 0.0) {
		[bgm fadeOutPause:static_cast<float>(fadeOut)];
	} else {
		$ECHO("Tried to pause a music with an invalid fade out time : " <<
			  fadeOut << " sec.");
	}
}

void AVAudioPlayerMusic::resume() {
	resume(0.0);
}

void AVAudioPlayerMusic::resume(double fadeIn) {
	assert(bgm);
	if(fadeIn >= 0.0) {
		[bgm fadeInResume:static_cast<float>(fadeIn)];
		playedOnce = true;
	} else {
		$ECHO("Tried to resume a music with an invalid fade in time : " <<
			  fadeIn << " sec.");
	}
}

bool AVAudioPlayerMusic::isLooping() {
	return [bgm isLooping];
}

AudioState::Enum AVAudioPlayerMusic::getCurrentState() {
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

AVAudioPlayerMusic::~AVAudioPlayerMusic() {
}

AVAudioPlayerMusic::AVAudioPlayerMusic(): BackgroundMusic(), bgm(NULL),
playedOnce(false) {
}

void AVAudioPlayerMusic::load(std::string const& filePath) {
	if(!bgm) {
		const char* tmp = filePath.c_str();
		bgm = [[AVAudioPlayerMusicDelegate alloc] initWithPath:[NSString stringWithCString:tmp]];
	}
}
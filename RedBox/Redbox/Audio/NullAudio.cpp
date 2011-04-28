#include "NullAudio.h"

#include "Debug.h"

using namespace RedBox;

void NullAudio::play(int nbTimes) {
	RB_ECHO("Playing a NullAudio object " << nbTimes << " times.");
}

void NullAudio::stop() {
	RB_ECHO("Stopping a NullAudio object.");
}

void NullAudio::pause() {
	RB_ECHO("Pausing a NullAudio object.");
}

void NullAudio::resume() {
	RB_ECHO("Resuming a NullAudio object.");
}

bool NullAudio::isLooping() {
	RB_ECHO("Checking if a NullAudio object is looping, returning false.");
	return false;
}

AudioState::Enum NullAudio::getCurrentState() {
	RB_ECHO("Getting a NullAudio object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void NullAudio::play(int nbTimes, double fadeIn) {
	RB_ECHO("Playing a NullAudio object " << nbTimes << " times with a " <<
			fadeIn << " second(s) fade in.");
}

void NullAudio::stop(double fadeOut) {
	RB_ECHO("Stopping a NullAudio object with a " << fadeOut <<
			" second(s) fade out.");
}

void NullAudio::pause(double fadeOut) {
	RB_ECHO("Pausing a NullAudio object with a " << fadeOut <<
			" second(s) fade out.");
}

void NullAudio::resume(double fadeIn) {
	RB_ECHO("Resuming a NullAudio object with a " << fadeOut <<
			" second(s) fade in.");
}

NullAudio::~NullAudio() {
	RB_ECHO("Destroying a NullAudio object.");
}

NullAudio::NullAudio() : BackgroundMusic(), SoundFX() {
	RB_ECHO("Constructing a NullAudio object.");
}

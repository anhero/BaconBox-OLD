#include "NullAudio.h"

#include "Console.h"

using namespace RedBox;

void NullAudio::play(int nbTimes) {
	Console::print("Playing a NullAudio object " + Console::toString(nbTimes) + " times.");
}

void NullAudio::stop() {
	Console::print("Stopping a NullAudio object.");
}

void NullAudio::pause() {
	Console::print("Pausing a NullAudio object.");
}

void NullAudio::resume() {
	Console::print("Resuming a NullAudio object.");
}

bool NullAudio::isLooping() {
	Console::print("Checking if a NullAudio object is looping, returning false.");
	return false;
}

AudioState::Enum NullAudio::getCurrentState() const {
	Console::print("Getting a NullAudio object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void NullAudio::play(int nbTimes, double fadeIn) {
	Console::print("Playing a NullAudio object " + Console::toString(nbTimes) + " times with a " +
			Console::toString(fadeIn) + " second(s) fade in.");
}

void NullAudio::stop(double fadeOut) {
	Console::print("Stopping a NullAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void NullAudio::pause(double fadeOut) {
	Console::print("Pausing a NullAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void NullAudio::resume(double fadeIn) {
	Console::print("Resuming a NullAudio object with a " + Console::toString(fadeIn) +
			" second(s) fade in.");
}

NullAudio::~NullAudio() {
	Console::print("Destroying a NullAudio object.");
}

NullAudio::NullAudio() : BackgroundMusic(), SoundFX() {
	Console::print("Constructing a NullAudio object.");
}

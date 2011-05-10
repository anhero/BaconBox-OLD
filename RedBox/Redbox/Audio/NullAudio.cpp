#include "NullAudio.h"

#include "Console.h"

using namespace RedBox;

void NullAudio::play(int nbTimes) {
	Console::Print("Playing a NullAudio object " + Console::ToString(nbTimes) + " times.");
}

void NullAudio::stop() {
	Console::Print("Stopping a NullAudio object.");
}

void NullAudio::pause() {
	Console::Print("Pausing a NullAudio object.");
}

void NullAudio::resume() {
	Console::Print("Resuming a NullAudio object.");
}

bool NullAudio::isLooping() {
	Console::Print("Checking if a NullAudio object is looping, returning false.");
	return false;
}

AudioState::Enum NullAudio::getCurrentState() const {
	Console::Print("Getting a NullAudio object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void NullAudio::play(int nbTimes, double fadeIn) {
	Console::Print("Playing a NullAudio object " + Console::ToString(nbTimes) + " times with a " +
			Console::ToString(fadeIn) + " second(s) fade in.");
}

void NullAudio::stop(double fadeOut) {
	Console::Print("Stopping a NullAudio object with a " + Console::ToString(fadeOut) +
			" second(s) fade out.");
}

void NullAudio::pause(double fadeOut) {
	Console::Print("Pausing a NullAudio object with a " + Console::ToString(fadeOut) +
			" second(s) fade out.");
}

void NullAudio::resume(double fadeIn) {
	Console::Print("Resuming a NullAudio object with a " + Console::ToString(fadeIn) +
			" second(s) fade in.");
}

NullAudio::~NullAudio() {
	Console::Print("Destroying a NullAudio object.");
}

NullAudio::NullAudio() : BackgroundMusic(), SoundFX() {
	Console::Print("Constructing a NullAudio object.");
}

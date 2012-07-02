#include "BaconBox/Audio/NullAudio.h"

#include "BaconBox/Console.h"

using namespace BaconBox;

void NullAudio::play(int nbTimes) {
	Console::println("Playing a NullAudio object " + Console::toString(nbTimes) + " times.");
}

void NullAudio::stop() {
	Console::println("Stopping a NullAudio object.");
}

void NullAudio::pause() {
	Console::println("Pausing a NullAudio object.");
}

void NullAudio::resume() {
	Console::println("Resuming a NullAudio object.");
}

bool NullAudio::isLooping() {
	Console::println("Checking if a NullAudio object is looping, returning false.");
	return false;
}

AudioState NullAudio::getCurrentState() const {
	Console::println("Getting a NullAudio object's audio state, returning STOPPED");
	return AudioState::STOPPED;
}

void NullAudio::play(int nbTimes, double fadeIn) {
	Console::println("Playing a NullAudio object " + Console::toString(nbTimes) + " times with a " +
			Console::toString(fadeIn) + " second(s) fade in.");
}

void NullAudio::stop(double fadeOut) {
	Console::println("Stopping a NullAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void NullAudio::pause(double fadeOut) {
	Console::println("Pausing a NullAudio object with a " + Console::toString(fadeOut) +
			" second(s) fade out.");
}

void NullAudio::resume(double fadeIn) {
	Console::println("Resuming a NullAudio object with a " + Console::toString(fadeIn) +
			" second(s) fade in.");
}

NullAudio::~NullAudio() {
	Console::println("Destroying a NullAudio object.");
}

NullAudio::NullAudio() : BackgroundMusic(), SoundFX() {
	Console::println("Constructing a NullAudio object.");
}

#include "AVAudioPlayerMusic.h"

#include "AudioState.h"
#include "BackgroundMusic.h"

using namespace RedBox;

void AVAudioPlayerMusic::play(int nbTimes) {
}

void AVAudioPlayerMusic::stop() {
}

void AVAudioPlayerMusic::pause() {
}

void AVAudioPlayerMusic::resume() {
}

bool AVAudioPlayerMusic::isLooping() {
	return false;
}

AudioState::Enum AVAudioPlayerMusic::getCurrentState() {
	return AudioState::INITIAL;
}

AVAudioPlayerMusic::~AVAudioPlayerMusic() {
}

AVAudioPlayerMusic::AVAudioPlayerMusic(): BackgroundMusic() {
}

void AVAudioPlayerMusic::load(std::string const &filePath) {
}
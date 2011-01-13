#include "AnimationParameters.h"
using namespace RedBox;

AnimationParameters::AnimationParameters (const std::string& newName, 
										  int setOfFrames[], int numberOfFrames,
										  double newFps): name(newName), 
timePerFrame(1.0 / ((newFps != 0.0)?(newFps):(1.0))), activeFrameIndex(0), lastUpdateTime(TimeHelper::TimeHelper::getSinceEpoch()) {
	//For each frames, adds them to the list.
	for (int i = 0; i < numberOfFrames; i++) {
		frames.push_back(setOfFrames[i]);
	}
}

AnimationParameters::~AnimationParameters() {
}

int AnimationParameters::getActiveFrame () {
	if (timePerFrame + lastUpdateTime < TimeHelper::TimeHelper::getSinceEpoch()) {
		lastUpdateTime += timePerFrame;
		activeFrameIndex = ++activeFrameIndex % frames.size();
	}
	return frames[activeFrameIndex];
	
	/*	double tickSinceLastTime = (tick - lastUpdateTime);
	 
	 //We should avoid making a condition here and just
	 //setup the lastUpdateTime to the last tick in the constructor.
	 if (lastUpdateTime == 0) {
	 lastUpdateTime = tick;
	 return frames[ActiveFrameIndex];
	 }
	 else {
	 if (tickSinceLastTime > (1.0/fps)) {
	 ActiveFrameIndex += tickSinceLastTime / (1.0/fps);
	 if (ActiveFrameIndex > frameCount) {
	 ActiveFrameIndex -= frameCount;
	 }
	 lastUpdateTime = tick;
	 }
	 return frames[(int) ActiveFrameIndex];
	 }
	 */
}

void AnimationParameters::reset () {
	lastUpdateTime = TimeHelper::TimeHelper::getSinceEpoch();
	activeFrameIndex = 0;
}

const std::string& AnimationParameters::getName() const {
	return name;
}

#include "AnimationParameters.h"

using namespace RedBox;

AnimationParameters::AnimationParameters(): timePerFrame(0.0), nbLoops(-1) {
}

AnimationParameters::AnimationParameters(const std::vector<unsigned int>& newFrames,
					double newTimePerFrame,
					int newNbLoops): frames(newFrames), 
timePerFrame(newTimePerFrame), nbLoops(newNbLoops) {
}
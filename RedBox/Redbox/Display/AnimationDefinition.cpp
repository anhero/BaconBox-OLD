#include "AnimationDefinition.h"

namespace RedBox {
	AnimationDefinition::AnimationDefinition(): frames(), timePerFrame(0.0),
		nbLoops(-1) {
	}

	AnimationDefinition::AnimationDefinition(const std::vector<unsigned int>& newFrames,
	                                         double newTimePerFrame,
	                                         int newNbLoops): frames(newFrames),
		timePerFrame(newTimePerFrame), nbLoops(newNbLoops) {
	}

	AnimationDefinition::AnimationDefinition(const AnimationDefinition &src) :
		frames(src.frames), timePerFrame(src.timePerFrame), nbLoops(src.nbLoops) {
	}

	AnimationDefinition &AnimationDefinition::operator=(const AnimationDefinition &src) {
		if (this != &src) {
			frames = src.frames;
			timePerFrame = src.timePerFrame;
			nbLoops = src.nbLoops;
		}

		return *this;
	}

	std::ostream &operator<<(std::ostream &output,
	                         const AnimationDefinition &a) {
		output << "{timePerFrame: ";
		output << a.timePerFrame << ", nbLoops: " << a.nbLoops << ", frames: [";

		for (std::vector<unsigned int>::const_iterator i = a.frames.begin(); i != a.frames.end(); ++i) {
			if (i != a.frames.begin()) {
				output << ", ";
			}

			output << *i;
		}

		output << "]}";
		return output;
	}
}

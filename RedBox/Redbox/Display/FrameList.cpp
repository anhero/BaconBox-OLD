#include "FrameList.h"

namespace RedBox {
	FrameList::FrameList() : frameSize(), frames() {
	}

	FrameList::FrameList(const Vector2 &newFrameSize,
	                     const FrameArray &newFrames) : frameSize(newFrameSize),
		frames(newFrames) {
	}

	FrameList::FrameList(const FrameList &src) : frameSize(src.frameSize),
		frames(src.frames) {
	}

	FrameList &FrameList::operator=(const FrameList &src) {
		if (this != &src) {
			frameSize = src.frameSize;
			frames = src.frames;
		}

		return *this;
	}

	std::ostream &operator<<(std::ostream &output, const FrameList &fl) {
		output << "{ \"frameSize\": " << fl.frameSize << ", \"frames\": ";

		for (FrameList::FrameArray::const_iterator i = fl.frames.begin();
		     i != fl.frames.end(); ++i) {
			if (i != fl.frames.begin()) {
				output << ", ";
			}

			output << *i;
		}

		output << "}";

		return output;
	}
}

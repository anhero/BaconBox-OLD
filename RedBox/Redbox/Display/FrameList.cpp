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
}

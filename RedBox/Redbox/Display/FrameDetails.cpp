#include "FrameDetails.h"

namespace RedBox {
	FrameDetails::FrameDetails() : position(), orientation(Orientation::NORTH) {
	}

	FrameDetails::FrameDetails(const Vector2 &newPosition,
	                           Orientation newOrientation) :
		position(newPosition), orientation(newOrientation) {
	}

	FrameDetails::FrameDetails(const FrameDetails &src) :
		position(src.position), orientation(src.orientation) {
	}

	FrameDetails &FrameDetails::operator=(const FrameDetails &src) {
		if (this != &src) {
			position = src.position;
			orientation = src.orientation;
		}

		return *this;
	}
}

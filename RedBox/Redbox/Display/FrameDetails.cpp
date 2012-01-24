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

	std::ostream &operator<<(std::ostream &output, const FrameDetails &fd) {
		output << "{\"position\": " << fd.position << ", \"orientation\": \"";
		switch (fd.orientation.underlying()) {
		case FrameDetails::Orientation::NORTH:
			output << "NORTH";
			break;
		case FrameDetails::Orientation::SOUTH:
			output << "SOUTH";
			break;
		case FrameDetails::Orientation::EAST:
			output << "EAST";
			break;
		case FrameDetails::Orientation::WEST:
			output << "WEST";
			break;
		default:
			break;
		}

		output << "\"}";
		return output;
	}
}

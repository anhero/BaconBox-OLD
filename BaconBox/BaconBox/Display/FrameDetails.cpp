#include "BaconBox/Display/FrameDetails.h"

#include "BaconBox/Helper/Serialization/DefaultSerializer.h"
#include "BaconBox/Helper/Serialization/Serializer.h"

namespace BaconBox {
	bool FrameDetails::isValidValue(const Value &node) {
		bool result = true;
		Object::const_iterator itPosition = node.getObject().find("position");

		if (itPosition != node.getObject().end()) {
			if (!Vector2::isValidValue(itPosition->second)) {
				result = false;
			}

		} else {
			result = false;
		}

		return result;
	}

	FrameDetails::FrameDetails() : position(), orientation(Orientation::NORTH) {
	}

	FrameDetails::FrameDetails(const Vector2 &newPosition,
	                           Orientation newOrientation) :
		position(newPosition), orientation(newOrientation) {
	}

	FrameDetails::FrameDetails(const FrameDetails &src) :
		position(src.position), orientation(src.orientation) {
	}

	FrameDetails::Orientation FrameDetails::stringToOrientation(const std::string &orientationString) {
		Orientation result = Orientation::NORTH;

		if (orientationString == std::string("NORTH")) {
			result = Orientation::NORTH;

		} else if (orientationString == std::string("EAST")) {
			result = Orientation::EAST;

		} else if (orientationString == std::string("WEST")) {
			result = Orientation::WEST;

		} else if (orientationString == std::string("SOUTH")) {
			result = Orientation::SOUTH;

		}

		return result;
	}

	FrameDetails &FrameDetails::operator=(const FrameDetails &src) {
		if (this != &src) {
			position = src.position;
			orientation = src.orientation;
		}

		return *this;
	}

	void FrameDetails::serialize(Value &node, bool setName) const {
		if (setName) {
			node.setName("FrameDetails");
		}

		DefaultSerializer::serialize(position, node["position"], false);

		switch (orientation.underlying()) {
		case Orientation::NORTH:
			node["orientation"] = "NORTH";
			break;

		case Orientation::SOUTH:
			node["orientation"] = "SOUTH";
			break;

		case Orientation::EAST:
			node["orientation"] = "EAST";
			break;

		case Orientation::WEST:
			node["orientation"] = "WEST";
			break;

		default:
			break;
		}

		node["orientation"].setAttribute(true);
	}

	bool FrameDetails::deserialize(const Value &node) {
		bool result = true;
		Object::const_iterator itPosition = node.getObject().find("position");
		Object::const_iterator itOrientation = node.getObject().find("orientation");

		if (itPosition != node.getObject().end()) {

			if (DefaultSerializer::deserialize(itPosition->second, position)) {
				if (itOrientation != node.getObject().end()) {
					orientation = FrameDetails::stringToOrientation(itOrientation->second.getString());

				} else {
					orientation = Orientation::NORTH;
				}

			} else {
				result = false;
			}

		} else {
			result = false;
		}

		return result;
	}

	std::ostream &operator<<(std::ostream &output, const FrameDetails &fd) {
		Value tmpValue;
		DefaultSerializer::serialize(fd, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}

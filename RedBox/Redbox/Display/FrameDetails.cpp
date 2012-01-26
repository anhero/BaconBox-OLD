#include "FrameDetails.h"

#include "DefaultSerializer.h"
#include "Serializer.h"

namespace RedBox {
	void FrameDetails::serialize(const FrameDetails &input, Value &node) {
		DefaultSerializer::serialize(input.position, node["position"]);

		switch (input.orientation.underlying()) {
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
	}

	bool FrameDetails::deserialize(const Value &node, FrameDetails &output) {
		bool result = true;
		Object::const_iterator itPosition = node.getObject().find("position");
		Object::const_iterator itOrientation = node.getObject().find("orientation");

		if (itPosition != node.getObject().end() &&
		    itPosition->second.isObject() &&
		    itOrientation != node.getObject().end() &&
		    itOrientation->second.isString()) {

			Vector2 tmpPosition;

			if (DefaultSerializer::deserialize(itPosition->second, tmpPosition)) {
				if (itOrientation->second.getString() == std::string("NORTH")) {
					output.position = tmpPosition;
					output.orientation = Orientation::NORTH;

				} else if (itOrientation->second.getString() == std::string("EAST")) {
					output.position = tmpPosition;
					output.orientation = Orientation::EAST;

				} else if (itOrientation->second.getString() == std::string("WEST")) {
					output.position = tmpPosition;
					output.orientation = Orientation::WEST;

				} else if (itOrientation->second.getString() == std::string("SOUTH")) {
					output.position = tmpPosition;
					output.orientation = Orientation::SOUTH;

				} else {
					result = false;
				}

			} else {
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

	FrameDetails &FrameDetails::operator=(const FrameDetails &src) {
		if (this != &src) {
			position = src.position;
			orientation = src.orientation;
		}

		return *this;
	}

	std::ostream &operator<<(std::ostream &output, const FrameDetails &fd) {
		Value tmpValue;
		DefaultSerializer::serialize(fd, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}

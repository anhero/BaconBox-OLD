#include "FrameDetails.h"

#include "DefaultSerializer.h"
#include "Serializer.h"

namespace RedBox {
	bool FrameDetails::isValidValue(const Value &node) {
		bool result = true;
		Object::const_iterator itPosition = node.getObject().find("position");
		Object::const_iterator itOrientation = node.getObject().find("orientation");

		if (itPosition != node.getObject().end() &&
		    itOrientation != node.getObject().end()) {
			if (Vector2::isValidValue(itPosition->second) &&
			    itOrientation->second.isString()) {
				if (itOrientation->second.getString() != std::string("NORTH") &&
				    itOrientation->second.getString() != std::string("EAST") &&
				    itOrientation->second.getString() != std::string("WEST") &&
				    itOrientation->second.getString() != std::string("SOUTH")) {
					result = false;
				}
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

	void FrameDetails::serialize(Value &node) const {
		DefaultSerializer::serialize(position, node["position"]);

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
	}

	bool FrameDetails::deserialize(const Value &node) {
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
					position = tmpPosition;
					orientation = Orientation::NORTH;

				} else if (itOrientation->second.getString() == std::string("EAST")) {
					position = tmpPosition;
					orientation = Orientation::EAST;

				} else if (itOrientation->second.getString() == std::string("WEST")) {
					position = tmpPosition;
					orientation = Orientation::WEST;

				} else if (itOrientation->second.getString() == std::string("SOUTH")) {
					position = tmpPosition;
					orientation = Orientation::SOUTH;

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

	std::ostream &operator<<(std::ostream &output, const FrameDetails &fd) {
		Value tmpValue;
		DefaultSerializer::serialize(fd, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}

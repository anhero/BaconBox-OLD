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
	}

	bool FrameDetails::deserialize(const Value &node) {
		bool result = true;
		Object::const_iterator itPosition = node.getObject().find("position");
		Object::const_iterator itOrientation = node.getObject().find("orientation");

		if (itPosition != node.getObject().end() &&
			itPosition->second.isObject()) {

			if (DefaultSerializer::deserialize(itPosition->second, position)) {
				if (itOrientation != node.getObject().end()) {
					if (itOrientation->second.getString() == std::string("NORTH")) {
						orientation = Orientation::NORTH;

					} else if (itOrientation->second.getString() == std::string("EAST")) {
						orientation = Orientation::EAST;

					} else if (itOrientation->second.getString() == std::string("WEST")) {
						orientation = Orientation::WEST;

					} else if (itOrientation->second.getString() == std::string("SOUTH")) {
						orientation = Orientation::SOUTH;

					} else {
						orientation = Orientation::NORTH;
					}
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

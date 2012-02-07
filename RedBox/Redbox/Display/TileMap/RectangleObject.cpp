#include "RectangleObject.h"

namespace RedBox {
	RectangleObject::RectangleObject(const Vector2 &newSize,
	                                 const Vector2 &newPosition,
	                                 const std::string &newName) :
		TileMapObject(newPosition, newName), size(newSize) {
	}

	RectangleObject::RectangleObject(float newWidth, float newHeight,
	                                 const Vector2 &newPosition,
	                                 const std::string &newName) :
		TileMapObject(newPosition, newName), size(newWidth, newHeight) {
	}

	RectangleObject::RectangleObject(const Vector2 &newSize,
	                                 float newXPosition, float newYPosition,
	                                 const std::string &newName) :
		TileMapObject(newXPosition, newYPosition, newName), size(newSize) {
	}

	RectangleObject::RectangleObject(float newWidth, float newHeight,
	                                 float newXPosition, float newYPosition,
	                                 const std::string &newName) :
		TileMapObject(newXPosition, newYPosition, newName),
		size(newWidth, newHeight) {
	}

	RectangleObject::RectangleObject(const RectangleObject &src) :
		TileMapObject(src), size(src.size) {
	}

	RectangleObject::~RectangleObject() {
	}

	RectangleObject &RectangleObject::operator=(const RectangleObject &src) {
		this->TileMapObject::operator=(src);

		if (this != &src) {
			size = src.size;
		}

		return *this;
	}
}

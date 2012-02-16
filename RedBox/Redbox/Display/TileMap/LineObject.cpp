#if 0
#include "LineObject.h"

namespace RedBox {
	LineObject::LineObject(const Vector2 &newPosition,
	                       const std::string &newName) :
		TileMapObject(newPosition, newName), vertices() {
	}

	LineObject::LineObject(float newXPosition, float newYPosition,
	                       const std::string &newName) :
		TileMapObject(newXPosition, newYPosition, newName), vertices() {
	}

	LineObject::LineObject(const LineObject &src) : TileMapObject(src),
		vertices(src.vertices) {
	}

	LineObject::~LineObject() {
	}

	LineObject &LineObject::operator=(const LineObject &src) {
		this->TileMapObject::operator=(src);

		if (this != &src) {
			vertices = src.vertices;
		}

		return *this;
	}
}
#endif

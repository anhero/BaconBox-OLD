#if 0
#include "PolygonObject.h"

namespace RedBox {
	PolygonObject::PolygonObject(const Vector2 &newPosition,
	                             const std::string &newName) :
	    TileMapObject(newPosition, newName), vertices() {
	}

	PolygonObject::PolygonObject(float newXPosition, float newYPosition,
	                             const std::string &newName) :
	    TileMapObject(newXPosition, newYPosition, newName), vertices() {
	}

	PolygonObject::PolygonObject(const PolygonObject &src) : TileMapObject(src),
	    vertices(src.vertices) {
	}

	PolygonObject::~PolygonObject() {
	}

	PolygonObject &PolygonObject::operator=(const PolygonObject &src) {
		this->TileMapObject::operator=(src);

		if (this != &src) {
			vertices = src.vertices;
		}

		return *this;
	}
}
#endif

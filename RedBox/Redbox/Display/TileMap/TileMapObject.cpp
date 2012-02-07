#include "TileMapObject.h"

namespace RedBox {
	TileMapObject::TileMapObject(const Vector2 &newPosition,
	                             const std::string &newName) :
		position(newPosition), name(newName), properties() {
	}

	TileMapObject::TileMapObject(float newXPosition,
	                             float newYPosition,
	                             const std::string &newName) :
		position(newXPosition, newYPosition), name(newName), properties() {
	}

	TileMapObject::TileMapObject(const TileMapObject &src) :
		position(src.position), name(src.name), properties(src.properties) {
	}

	TileMapObject::~TileMapObject() {
	}

	TileMapObject &TileMapObject::operator=(const TileMapObject &src) {
		if (this != &src) {
			position = src.position;
			name = src.name;
			properties = src.properties;
		}

		return *this;
	}
}

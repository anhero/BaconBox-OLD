#include "TileObject.h"

namespace RedBox {
	TileObject::TileObject(unsigned int newTileIndex,
	                       const Vector2 &newPosition,
	                       const std::string &newName) :
		TileMapObject(newPosition, newName), tileIndex(newTileIndex) {
	}

	TileObject::TileObject(unsigned int newTileIndex,
	                       float newXPosition,
	                       float newYPosition,
	                       const std::string &newName) :
		TileMapObject(newXPosition, newYPosition, newName),
		tileIndex(newTileIndex) {
	}

	TileObject::TileObject(const TileObject &src) : TileMapObject(src),
		tileIndex(src.tileIndex) {
	}

	TileObject::~TileObject() {
	}

	TileObject &TileObject::operator=(const TileObject &src) {
		this->TileMapObject::operator=(src);

		if (this != &src) {
			tileIndex = src.tileIndex;
		}

		return *this;
	}
}

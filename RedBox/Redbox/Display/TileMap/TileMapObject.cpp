#include "TileMapObject.h"

namespace RedBox {
	TileMapObject::TileMapObject(const std::string &newName,
								 const Vector2 &newPosition) :
		TileMapEntity(newName), Positionable(newPosition) {
	}

	TileMapObject::TileMapObject(const TileMapObject &src) : TileMapEntity(src),
		Positionable(src) {
	}

	TileMapObject::~TileMapObject() {
	}

	TileMapObject &TileMapObject::operator=(const TileMapObject &src) {
		this->TileMapEntity::operator=(src);
		this->Positionable::operator=(src);

		return *this;
	}
}

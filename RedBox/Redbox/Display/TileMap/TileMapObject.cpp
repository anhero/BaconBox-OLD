#include "TileMapObject.h"

#include "ObjectLayer.h"

namespace RedBox {
	TileMapObject::TileMapObject(const std::string &newName,
	                             const Vector2 &newPosition,
	                             const ObjectLayer &newParentLayer) :
		TileMapEntity(newName), Positionable(newPosition),
		parentLayer(newParentLayer) {
	}

	TileMapObject::TileMapObject(const TileMapObject &src,
	                             const ObjectLayer &newParentLayer) : TileMapEntity(src),
		Positionable(src), parentLayer(newParentLayer) {
	}

	TileMapObject::~TileMapObject() {
	}
}

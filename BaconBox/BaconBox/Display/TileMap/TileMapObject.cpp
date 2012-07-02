#include "BaconBox/Display/TileMap/TileMapObject.h"

#include "BaconBox/Display/TileMap/ObjectLayer.h"

namespace BaconBox {
	TileMapObject::TileMapObject(const std::string &newName,
	                             const Vector2 &newPosition,
	                             const ObjectLayer &newParentLayer,
								 const std::string &newType) :
		TileMapEntity(newName), Positionable(newPosition),
		parentLayer(newParentLayer), type(newType) {
	}

	TileMapObject::TileMapObject(const TileMapObject &src,
	                             const ObjectLayer &newParentLayer) : TileMapEntity(src),
		Positionable(src), parentLayer(newParentLayer) {
	}

	TileMapObject::~TileMapObject() {
	}
	
	const std::string &TileMapObject::getType() const {
		return type;
	}
	
	void TileMapObject::setType(const std::string &newType) {
		type = newType;
	}
}

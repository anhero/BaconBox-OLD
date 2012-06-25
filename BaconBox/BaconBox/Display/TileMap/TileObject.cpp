#include "TileObject.h"

#include "ObjectLayer.h"
#include "TileMap.h"
#include "Tileset.h"

namespace BaconBox {
	void TileObject::setName(const std::string &newName) {
		if (!parentLayer.getTile(newName)) {
			this->TileMapObject::setName(newName);
			parentLayer.dirtyTileNames = true;
		}
	}

	const Vector2 TileObject::getSize() const {
		if (tileId > 0) {
			return parentLayer.parentMap.getTileset(tileId)->getTileSize();

		} else {
			return Vector2();
		}
	}

	float TileObject::getWidth() const {
		if (tileId > 0) {
			return parentLayer.parentMap.getTileset(tileId)->getTileWidth();

		} else {
			return 0.0f;
		}
	}

	float TileObject::getHeight() const {
		if (tileId > 0) {
			return parentLayer.parentMap.getTileset(tileId)->getTileHeight();

		} else {
			return 0.0f;
		}
	}

	unsigned int TileObject::getTileId() const {
		return tileId;
	}

	void TileObject::setTileId(unsigned int newTileId) {
		if (parentLayer.parentMap.getTileset(newTileId) || newTileId == 0u) {
			tileId = newTileId;
		}
	}

	TileObject::TileObject(const std::string &newName,
	                       const Vector2 &newPosition,
	                       const ObjectLayer &newParentLayer,
	                       unsigned int newTileId) :
		TileMapObject(newName, newPosition, newParentLayer),
		tileId((parentLayer.parentMap.getTileset(newTileId)) ? (newTileId) : (0u)) {
	}

	TileObject::TileObject(const TileObject &src,
	                       const ObjectLayer &newObjectLayer) :
		TileMapObject(src, newObjectLayer), tileId(src.tileId) {
	}

	TileObject::~TileObject() {
	}

	void TileObject::applyTilesetDestruction(const TileIdRange &toDestroy) {
		if (toDestroy.isWithinRange(tileId)) {
			tileId = 0;

		} else if (tileId >= toDestroy.max) {
			tileId -= toDestroy.max - toDestroy.min;
		}
	}
}

#include "TileObject.h"

#include "TileMap.h"
#include "Tileset.h"

namespace RedBox {
	const Vector2 TileObject::getSize() const {
		if (tileId > 0) {
			return parentMap.getTileset(tileId)->getTileSize();

		} else {
			return Vector2();
		}
	}

	float TileObject::getWidth() const {
		if (tileId > 0) {
			return parentMap.getTileset(tileId)->getTileWidth();

		} else {
			return 0.0f;
		}
	}

	float TileObject::getHeight() const {
		if (tileId > 0) {
			return parentMap.getTileset(tileId)->getTileHeight();

		} else {
			return 0.0f;
		}
	}

	unsigned int TileObject::getTileId() const {
		return tileId;
	}

	void TileObject::setTileId(unsigned int newTileId) {
		if (parentMap.getTileset(newTileId) || newTileId == 0) {
			tileId = newTileId;
		}
	}

	TileObject::TileObject(const std::string &newName,
	                       const Vector2 &newPosition,
	                       const TileMap &newParentMap,
	                       unsigned int newTileId) : TileMapObject(newName, newPosition),
		parentMap(newParentMap),
		tileId((parentMap.getTileset(newTileId)) ? (newTileId) : (0)) {
	}

	TileObject::TileObject(const TileObject &src, const TileMap &newParentMap) :
		TileMapObject(src), parentMap(newParentMap), tileId(src.tileId) {
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

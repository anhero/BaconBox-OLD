#include "BatchedTile.h"

#include "Tileset.h"
#include "ShapeFactory.h"

namespace RedBox {
	BatchedTile::BatchedTile() : BatchedInanimateSprite(), tileset(NULL),
		tileId(0u) {
	}

	BatchedTile::BatchedTile(Tileset *newTileset,
	                         unsigned int newTileId,
	                         const Vector2 &startingPosition) :
		BatchedInanimateSprite(), tileset(newTileset), tileId(0u) {
		this->Collidable::setPosition(startingPosition.getX(), startingPosition.getY());
		construct(tileset, newTileId);
	}

	BatchedTile::BatchedTile(const BatchedTile &src) :
		BatchedInanimateSprite(src), tileset(src.tileset), tileId(src.tileId) {
	}

	BatchedTile::~BatchedTile() {
	}

	BatchedTile &BatchedTile::operator=(const BatchedTile &src) {
		this->BatchedInanimateSprite::operator=(src);

		if (this != &src) {
			tileset = src.tileset;
			tileId = src.tileId;
		}

		return *this;
	}

	BatchedTile *BatchedTile::clone() const {
		return new BatchedTile(*this);
	}

	unsigned int BatchedTile::getTileId() const {
		return tileId;
	}

	void BatchedTile::setTileId(unsigned int newTileId) {
		// We check if the current tileset is valid.
		if (tileset) {
			// If so, we check if the tile id fits into the tileset.
			if (tileset->isIdInTileset(newTileId)) {
				// We set the new tile id.
				tileId = newTileId;

				// We refresh the tile's texture coordinates.
				this->reconstruct();
			}

		} else {
			// We don't have a tileset assigned, so we don't care what tile id
			// we have yet.
			tileId = newTileId;
		}
	}

	Tileset *BatchedTile::getTileset() const {
		return tileset;
	}

	void BatchedTile::reconstruct() {
		// We make sure the tile id is valid.
		if (tileset && tileId &&
		    tileset->getTileWidth() >= 0.0f &&
		    tileset->getTileHeight() >= 0.0f) {

			this->getVertices().resize(4);
			ShapeFactory::createRectangle(tileset->getTileSize(), this->getPosition(), &(this->getVertices()));

			tileset->loadTextureCoordinates(tileId, this->getTextureCoordinates());
		}
	}

	void BatchedTile::construct(Tileset *newTileset, unsigned int newTileId) {
		tileset = newTileset;
		tileId = newTileId;

		// We make sure the tileset is valid.
		if (tileset) {
			tileId = tileset->isIdInTileset(newTileId);
			this->setTextureInformation(tileset->getTextureInformation());

			reconstruct();
		}
	}
}

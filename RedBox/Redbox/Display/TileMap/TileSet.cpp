#include "TileSet.h"

namespace RedBox {
	TileSet::TileSet() : Texturable(), name(DEFAULT_NAME),
		tileSize(DEFAULT_TILE_SIZE) {
	}

	TileSet::TileSet(TexturePointer &newTexture,
	                 const std::string &newName,
	                 const Vector2 &newTileSize) : Texturable(newTexture),
		name(newName), tileSize(newTileSize) {
	}

	TileSet::TileSet(TexturePointer &newTexture,
	                 const std::string &newName,
	                 float newTileWidth,
	                 float newTileHeight) : Texturable(newTexture),
		name(newName), tileSize(newTileWidth, newTileHeight) {
	}

	TileSet::TileSet(const TileSet &src) : Texturable(src), name(src.name),
		tileSize(src.tileSize) {
	}

	TileSet &TileSet::operator=(const TileSet &src) {
		this->TileSet::operator=(src);

		if (this != &src) {
			name = src.name;
			tileSize = src.tileSize;
		}

		return *this;
	}

	const std::string TileSet::getName() const {
		return name;
	}

	void TileSet::setName(const std::string &newName) {
		name = newName;
	}

	const Vector2 &TileSet::getTileSize() const {
		return tileSize;
	}

	void TileSet::setTileSize(const Vector2 &newTileSize) {
		tileSize = newTileSize;
	}

	void TileSet::setTileSize(float newTileWidth, float newTileHeight) {
		tileSize.setXY(newTileWidth, newTileHeight);
	}

	float TileSet::getTileWidth() const {
		return tileSize.getX();
	}

	void TileSet::setTileWidth(float newTileWidth) {
		tileSize.setX(newTileWidth);
	}

	float TileSet::getTileHeight() const {
		return tileSize.getY();
	}

	void TileSet::setTileHeight(float newTileHeight) {
		tileSize.setY(newTileHeight);
	}
}

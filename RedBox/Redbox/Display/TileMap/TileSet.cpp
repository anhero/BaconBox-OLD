#include "TileSet.h"

#include "TextureInformation.h"

namespace RedBox {
	const Vector2 TileSet::DEFAULT_TILE_SIZE = Vector2(32.0f, 32.0f);

	TileSet::TileSet() : textureInformation(NULL), tileSize(DEFAULT_TILE_SIZE),
		tileSpacing(0.0f), margin(0.0f), tileOffset(),
		tileColor(Color::WHITE), properties() {
	}

	TileSet::TileSet(TexturePointer newTexture,
	                 const Vector2 &newTileSize,
	                 float newTileSpacing,
	                 float newMargin,
	                 const Vector2 &newTileOffset) :
		textureInformation(newTexture.pointer), tileSize(newTileSize),
		tileSpacing(newTileSpacing), margin(newMargin),
		tileOffset(newTileOffset), tileColor(Color::WHITE), properties() {
	}

	TileSet::TileSet(TexturePointer newTexture,
	                 float newTileWidth,
	                 float newTileHeight,
	                 float newTileSpacing,
	                 float newMargin,
	                 const Vector2 &newTileOffset) :
		textureInformation(newTexture.pointer),
		tileSize(newTileWidth, newTileHeight), tileSpacing(newTileSpacing),
		margin(newMargin), tileOffset(newTileOffset), tileColor(Color::WHITE),
		properties() {
	}

	TileSet::TileSet(const TileSet &src) :
		textureInformation(src.textureInformation), tileSize(src.tileSize),
		tileSpacing(src.tileSpacing), margin(src.margin),
		tileOffset(src.tileOffset), tileColor(src.tileColor),
		properties(src.properties) {
	}

	TileSet &TileSet::operator=(const TileSet &src) {
		if (this != &src) {
			textureInformation = src.textureInformation;
			tileSize = src.tileSize;
			tileSpacing = src.tileSpacing;
			margin = src.margin;
			tileOffset = src.tileOffset;
			tileColor = src.tileColor;
			properties = src.properties;
		}

		return *this;
	}
}

#include "Tileset.h"

#include <cassert>

#include "TileMap.h"
#include "TextureInformation.h"
#include "TileIdRange.h"

namespace RedBox {
	void Tileset::setName(const std::string &newName) {
		if (!parentMap.getTileset(newName)) {
			this->TileMapEntity::setName(newName);
			parentMap.dirtyTilesetsByName = true;
		}
	}

	TextureInformation *Tileset::getTextureInformation() const {
		return textureInformation;
	}

	const Vector2 &Tileset::getTileSize() const {
		return tileSize;
	}

	float Tileset::getTileWidth() const {
		return tileSize.getX();
	}

	float Tileset::getTileHeight() const {
		return tileSize.getY();
	}

	float Tileset::getTileSpacing() const {
		return tileSpacing;
	}

	float Tileset::getMargin() const {
		return margin;
	}

	const Vector2 &Tileset::getTileOffset() const {
		return tileOffset;
	}

	float Tileset::getXTileOffset() const {
		return tileOffset.getX();
	}

	float Tileset::getYTileOffset() const {
		return tileOffset.getY();
	}

	bool Tileset::loadTextureCoordinates(unsigned int tileId,
	                                     TextureCoordinates &textureCoordinates) const {
		// We make sure the tile id is valid.
		if (isIdInTileset(tileId)) {
			textureCoordinates = tileTextureCoordinates[tileId - firstTileId];
			return true;

		} else {
			return false;
		}
	}

	Tileset::TileCoordinates::size_type Tileset::getNbTiles() const {
		return tileTextureCoordinates.size();
	}

	unsigned int Tileset::getFirstTileId() const {
		return firstTileId;
	}

	unsigned int Tileset::validateTileId(unsigned int tileId) const {
		return (isIdInTileset(tileId)) ? (tileId) : (0u);
	}

	bool Tileset::isIdInTileset(unsigned int tileId) const {
		return TileIdRange(firstTileId, firstTileId + tileTextureCoordinates.size()).isWithinRange(tileId);
	}

	Tileset::Tileset(const std::string &newName,
	                 const TileMap &newParentMap,
	                 TextureInformation *newTextureInformation,
	                 const Vector2 &newTileSize,
	                 float newTileSpacing,
	                 float newMargin,
	                 const Vector2 &newTileOffset,
	                 unsigned int newFirstTileId) : TileMapEntity(newName),
		parentMap(newParentMap), textureInformation(newTextureInformation),
		tileSize(newTileSize), tileSpacing(newTileSpacing), margin(newMargin),
		tileOffset(newTileOffset), firstTileId(newFirstTileId),
		tileTextureCoordinates() {
		initializeTextureCoordinates();
	}

	Tileset::Tileset(const Tileset &src, const TileMap &newParentMap) :
		TileMapEntity(src), parentMap(newParentMap),
		textureInformation(src.textureInformation), tileSize(src.tileSize),
		tileSpacing(src.tileSpacing), margin(src.margin),
		tileOffset(src.tileOffset), firstTileId(src.firstTileId),
		tileTextureCoordinates(src.tileTextureCoordinates) {
	}

	Tileset::~Tileset() {
	}

	void Tileset::setFirstTileId(unsigned int newFirstTileId) {
		if (newFirstTileId > 0) {
			firstTileId = newFirstTileId;
		}
	}

	void Tileset::initializeTextureCoordinates() {
		// We make sure we have a valid texture information.
		if (textureInformation) {
			// The tile texture coordinates should be empty here.
			assert(tileTextureCoordinates.empty());

			// We calculate the upper left corner and lower right corner
			// to take into account the margin.
			Vector2 upperLeftCorner(margin / static_cast<float>(textureInformation->poweredWidth),
			                        margin / static_cast<float>(textureInformation->poweredHeight));
			Vector2 lowerRightCorner((static_cast<float>(textureInformation->imageWidth) - margin) / static_cast<float>(textureInformation->poweredWidth),
			                         (static_cast<float>(textureInformation->imageHeight) - margin) / static_cast<float>(textureInformation->poweredHeight));

			// We make sure the corners make sense.
			if (upperLeftCorner.getX() < lowerRightCorner.getX() &&
			    upperLeftCorner.getY() < lowerRightCorner.getY()) {

				float realTileSpacing = tileSpacing / static_cast<float>(textureInformation->poweredWidth);

				Vector2 realOffset = upperLeftCorner;
				Vector2 realTileSize = tileSize / Vector2(static_cast<float>(textureInformation->poweredWidth), static_cast<float>(textureInformation->poweredHeight));

				// We make sure there is enough room for at least one tile...
				if (realOffset.getX() + realTileSize.getX() < lowerRightCorner.getX()) {
					while (realOffset.getY() + realTileSize.getY() <= lowerRightCorner.getY()) {

						// We load the texture coordinates.
						tileTextureCoordinates.push_back(TextureCoordinates(4, realOffset));
						tileTextureCoordinates.back()[1].addToX(realTileSize.getX());
						tileTextureCoordinates.back()[2].addToY(realTileSize.getY());
						tileTextureCoordinates.back()[3].addToXY(realTileSize);

						// We increase the offset to the next tile's upper left
						// corner.
						realOffset.addToX(realTileSize.getX() + realTileSpacing);

						if (realOffset.getX() + realTileSize.getX() > lowerRightCorner.getX()) {
							realOffset.setX(upperLeftCorner.getX());
							realOffset.addToY(realTileSize.getY() + realTileSpacing);
						}
					}
				}
			}
		}
	}
}

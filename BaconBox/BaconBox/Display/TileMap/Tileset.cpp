#include "BaconBox/Display/TileMap/Tileset.h"

#include <cassert>

#include <algorithm>

#include "BaconBox/Display/TileMap/TileMap.h"
#include "BaconBox/Display/TextureInformation.h"
#include "BaconBox/Display/TileMap/TileIdRange.h"

namespace BaconBox {
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
		return tileSize.x;
	}

	float Tileset::getTileHeight() const {
		return tileSize.y;
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
		return tileOffset.x;
	}

	float Tileset::getYTileOffset() const {
		return tileOffset.y;
	}

	bool Tileset::loadTextureCoordinates(unsigned int tileId,
	                                     TextureCoordinates &textureCoordinates) const {
		// We make sure the tile id is valid.
		if (isIdInTileset(tileId)) {
			textureCoordinates = tileTextureCoordinates[TileIdRange::withoutFlipFlags(tileId) - firstTileId];

			assert(!textureCoordinates.empty());

			if (TileIdRange::isFlippedHorizontally(tileId)) {
				// We flip the texture coordinates to flip the tile
				// horizontally.
				std::swap(textureCoordinates[0], textureCoordinates[1]);
				std::swap(textureCoordinates[2], textureCoordinates[3]);
			}

			if (TileIdRange::isFlippedVertically(tileId)) {
				// We flip the texture coordinates to flip the tile vertically.
				std::swap(textureCoordinates[0], textureCoordinates[2]);
				std::swap(textureCoordinates[1], textureCoordinates[3]);
			}

			if (TileIdRange::isFlippedDiagonally(tileId)) {
				// We flip the texture coordinates to flip the tile
				// diagonally.
				std::swap(textureCoordinates[0], textureCoordinates[3]);
				std::swap(textureCoordinates[1], textureCoordinates[2]);
			}

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

	PropertyMap *Tileset::getTileProperties(unsigned int tileId) {
		if (TileIdRange(firstTileId, firstTileId + tileTextureCoordinates.size()).isWithinRange(tileId)) {
			return &tileProperties[TileIdRange::withoutFlipFlags(tileId)];

		} else {
			return NULL;
		}
	}

	const PropertyMap *Tileset::getTileProperties(unsigned int tileId) const {
		if (TileIdRange(firstTileId, firstTileId + tileTextureCoordinates.size()).isWithinRange(tileId)) {
			TileProperties::const_iterator found = tileProperties.find(TileIdRange::withoutFlipFlags(tileId));

			if (found != tileProperties.end()) {
				return &found->second;

			} else {
				return NULL;
			}

		} else {
			return NULL;
		}
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
		tileTextureCoordinates(), tileProperties() {
		initializeTextureCoordinates();
	}

	Tileset::Tileset(const Tileset &src, const TileMap &newParentMap) :
		TileMapEntity(src), parentMap(newParentMap),
		textureInformation(src.textureInformation), tileSize(src.tileSize),
		tileSpacing(src.tileSpacing), margin(src.margin),
		tileOffset(src.tileOffset), firstTileId(src.firstTileId),
		tileTextureCoordinates(src.tileTextureCoordinates),
		tileProperties(src.tileProperties) {
	}

	Tileset::~Tileset() {
	}

	void Tileset::setFirstTileId(unsigned int newFirstTileId) {
		if (newFirstTileId > 0) {
			TileProperties tmpBackup(tileProperties);
			tileProperties.clear();

			if (newFirstTileId < firstTileId) {
				unsigned int toRemove = firstTileId - newFirstTileId;

				for (TileProperties::iterator i = tmpBackup.begin();
				     i != tmpBackup.end(); ++i) {
					tileProperties.insert(std::make_pair(i->first - toRemove, i->second));
				}

			} else if (newFirstTileId > firstTileId) {
				unsigned int toAdd = newFirstTileId - firstTileId;

				for (TileProperties::iterator i = tmpBackup.begin();
				     i != tmpBackup.end(); ++i) {
					tileProperties.insert(std::make_pair(i->first + toAdd, i->second));
				}
			}

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
			if (upperLeftCorner.x < lowerRightCorner.x &&
			    upperLeftCorner.y < lowerRightCorner.y) {

				float realTileSpacing = tileSpacing / static_cast<float>(textureInformation->poweredWidth);

				Vector2 realOffset = upperLeftCorner;
				Vector2 realTileSize = tileSize.getCoordinatesDivision(Vector2(static_cast<float>(textureInformation->poweredWidth), static_cast<float>(textureInformation->poweredHeight)));

				// We make sure there is enough room for at least one tile...
				if (realOffset.x + realTileSize.x < lowerRightCorner.x) {
					while (realOffset.y + realTileSize.y <= lowerRightCorner.y) {

						// We load the texture coordinates.
						tileTextureCoordinates.push_back(TextureCoordinates(4, realOffset));
						tileTextureCoordinates.back()[1].x += realTileSize.x;
						tileTextureCoordinates.back()[2].y += realTileSize.y;
						tileTextureCoordinates.back()[3] += realTileSize;

						// We increase the offset to the next tile's upper left
						// corner.
						realOffset += Vector2::XComponent(realTileSize.x + realTileSpacing);

						if (realOffset.x + realTileSize.x > lowerRightCorner.x) {
							realOffset.x = upperLeftCorner.x;
							realOffset += Vector2::YComponent(realTileSize.y + realTileSpacing);
						}
					}
				}
			}
		}
	}
}

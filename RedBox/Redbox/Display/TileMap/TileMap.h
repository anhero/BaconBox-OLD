/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_H
#define RB_TILE_MAP_H

#include <map>
#include <vector>
#include <list>

#include "TileCoordinate.h"
#include "TileIdRange.h"
#include "Vector2.h"

namespace RedBox {
	class Tileset;
	class TileMapLayer;
	struct TextureInformation;

	class TileMap {
		friend class Tileset;
	public:

		TileMap();

		TileMap(const TileMap &src);

		~TileMap();

		TileMap &operator=(const TileMap &src);

		const TileCoordinate &getSizeInTiles() const;

		void setSizeInTiles(const TileCoordinate &newSizeInTiles);

		int getWidthInTiles() const;

		void setWidthInTiles(int newWidthInTiles);

		int getHeightInTiles() const;

		void setHeightInTiles(int newHeightInTiles);

		/**
		 * Finds the tileset that has a specific tile id in its range.
		 * @param tileId Id of the tile in the tileset to find.
		 * @return Pointer to the tileset found. NULL if the tile id is too
		 * high.
		 */
		const Tileset *getTileset(unsigned int tileId) const;

		/**
		 * Finds a tileset by its name.
		 * @param name Name of the tileset to find.
		 * @return Pointer to the tileset found. NULL if no tileset was found
		 * with the given name.
		 */
		const Tileset *getTileset(const std::string &name) const;

		/**
		 * Adds a tileset to the tile map.
		 * @param newName Name of the tileset.
		 * @param newTextureInformation Pointer to the texture information to
		 * use for the tileset.
		 * @param newTileSize Size of the tiles (in pixels). 32x32 by default.
		 * @param newTileSpacing Spacing between the tiles in the tileset image.
		 * @param newMargin Margin around the tiles in the tileset image.
		 * @param tileOffset Offset that is applied when drawing the tiles in
		 * this tileset.
		 * @param overwrite Set this to true if you want to overwrite the
		 * existing tileset if there is already a tileset with the same name.
		 */
		const Tileset *addTileset(const std::string &newName,
		                          TextureInformation *newTextureInformation,
		                          const Vector2 &newTileSize,
		                          float newTileSpacing = 0.0f,
		                          float newMargin = 0.0f,
		                          const Vector2 &newTileOffset = Vector2(),
		                          bool overwrite = false);

		/**
		 * Finds the tileset by its name and removes it, does nothing if no
		 * tileset have that name.
		 * @param tilesetName Name of the tileset to remove.
		 * @see RedBox::TileMap::removeTileset(const Tileset *tileset)
		 */
		void removeTileset(const std::string &tilesetName);

		/**
		 * Finds the tileset in the list of tilesets and removes it from the
		 * tilemap. Tile id's that referenced this tileset will be reset to 0.
		 * @param tileset Pointer to the tileset to remove.
		 */
		void removeTileset(const Tileset *tileset);
	private:

		typedef std::list<Tileset *> TilesetContainer;
		typedef std::map<TileIdRange, const Tileset *, TileIdRange::Comparator> TilesetMapByTileId;
		typedef std::map<std::string, const Tileset *> TilesetMapByName;
		typedef std::list<TileMapLayer *> LayerContainer;

		/**
		 * Refreshes the map of tilesets by their id.
		 */
		void refreshTilesetsByTileId();

		/**
		 * Refreshes the map of tilesets by their name.
		 */
		void refreshTilesetsByName() const;

		/**
		 * Applies the tile id changes to all of the layers for the tile id's
		 * of a tileset that was deleted.
		 * @param toDestroy Range of tile id's that were destroyed and must now
		 * be reset to 0.
		 */
		void applyTilesetDestruction(const TileIdRange &toDestroy);

		void deleteLayers();
		void deleteTilesets();

		TileCoordinate sizeInTiles;

		TilesetContainer tilesets;

		TilesetMapByTileId tilesetsByTileId;

		mutable TilesetMapByName tilesetsByName;

		mutable bool dirtyTilesetsByName;

		LayerContainer layers;
	};
}

#endif

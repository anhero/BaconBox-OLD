/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_LAYER_H
#define RB_TILE_LAYER_H

#include <stdint.h>

#include <vector>

#include "TileMapLayer.h"
#include "TileCoordinate.h"
#include "TileIdRange.h"

namespace RedBox {
	class TileLayer : public TileMapLayer {
		friend class TileMap;
	public:
		typedef std::vector<unsigned int> DataContainer;

		const TileCoordinate &getSizeInTiles() const;

		int getWidthInTiles() const;

		int getHeightInTiles() const;

		TileLayer *asTileLayer();

		const TileLayer *asTileLayer() const;

		unsigned int getTileId(const TileCoordinate &tileCoordinate) const;

		unsigned int getTileId(int xTileCoordinate, int yTileCoordinate) const;

		void setTileId(const TileCoordinate &tileCoordinate, unsigned int newTileId);

		void setTileId(int xTileCoordinate, int yTileCoordinate, unsigned int newTileId);
	private:
		explicit TileLayer(const TileMap *newParentMap,
		                   const std::string &newName = std::string());

		~TileLayer();

		void setSizeInTiles(const TileCoordinate &newSizeInTiles);
		void setWidthInTiles(int newWidth);
		void setHeightInTiles(int newHeight);

		void applyTilesetDestruction(const TileIdRange &toDestroy);

		DataContainer data;

		int32_t opacity;

		bool visible;
	};
}

#endif // RB_TILE_LAYER_H

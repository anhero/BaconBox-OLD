/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_LAYER_H
#define RB_TILE_LAYER_H

#include "TileMapLayer.h"
#include "TileCoordinate.h"

namespace RedBox {
	class TileLayer : public TileMapLayer {
	public:
	private:
		TileCoordinate sizeInTiles;
	};
}

#endif // RB_TILE_LAYER_H

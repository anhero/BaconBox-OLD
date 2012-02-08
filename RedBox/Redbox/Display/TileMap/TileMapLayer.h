/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_LAYER_H
#define RB_TILE_MAP_LAYER_H

#include "Layerable.h"
#include "Colorable.h"
#include "Positionable.h"
#include "TileMapEntity.h"

namespace RedBox {
	class ObjectLayer;
	class TileLayer;

	class TileMapLayer : public Colorable, public Layerable,
		public Positionable, public TileMapEntity {
	public:
		explicit TileMapLayer(const std::string &newName = std::string());

		TileMapLayer(const TileMapLayer &src);

		virtual ~TileMapLayer();

		TileMapLayer &operator=(const TileMapLayer &src);

		virtual ObjectLayer *getObjectLayer();

		virtual TileLayer *getTileLayer();
	};
}

#endif

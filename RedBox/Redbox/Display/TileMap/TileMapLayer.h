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

	/**
	 * Represents a tile map layer. ObjectLayer and TileLayer are derived from
	 * this class.
	 * @see RedBox::TileLayer
	 * @see RedBox::ObjectLayer
	 * @ingroup TileMap
	 */
	class TileMapLayer : public Colorable, public Layerable,
		public Positionable, public TileMapEntity {
	public:
		explicit TileMapLayer(const std::string &newName = std::string());

		TileMapLayer(const TileMapLayer &src);

		virtual ~TileMapLayer();

		TileMapLayer &operator=(const TileMapLayer &src);

		virtual ObjectLayer *asObjectLayer();
		virtual const ObjectLayer *asObjectLayer() const;

		virtual TileLayer *asTileLayer();
		virtual const TileLayer *asTileLayer() const;

		virtual TileMapLayer *clone() const = 0;
	};
}

#endif

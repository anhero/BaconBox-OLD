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
	class TileMap;

	/**
	 * Represents a tile map layer. ObjectLayer and TileLayer are derived from
	 * this class.
	 * @see RedBox::TileLayer
	 * @see RedBox::ObjectLayer
	 * @see RedBox::TileMap
	 * @ingroup TileMap
	 */
	class TileMapLayer : public TileMapEntity {
		friend class TileMap;
	public:
		virtual ObjectLayer *asObjectLayer();
		virtual const ObjectLayer *asObjectLayer() const;

		virtual TileLayer *asTileLayer();
		virtual const TileLayer *asTileLayer() const;
	protected:
		explicit TileMapLayer(const TileMap *newParentMap,
		                      const std::string &newName = std::string());
		virtual ~TileMapLayer();

		const TileMap *parentMap;
	private:

		TileMapLayer(const TileMapLayer &src);
		TileMapLayer &operator=(const TileMapLayer &src);
	};
}

#endif

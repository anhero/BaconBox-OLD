/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_GRAPHIC_OBJECT_LAYER_H
#define RB_GRAPHIC_OBJECT_LAYER_H

#include <vector>

#include "GraphicTileMapLayer.h"
#include "Sprite.h"
#include "InanimateSprite.h"

namespace RedBox {
	class ObjectLayer;
	class GraphicObjectLayer : public GraphicTileMapLayer {
	public:
		GraphicObjectLayer();
		GraphicObjectLayer(const ObjectLayer &layer);
		GraphicObjectLayer(const GraphicObjectLayer &src);
		~GraphicObjectLayer();
		GraphicObjectLayer &operator=(const GraphicObjectLayer &src);

		void construct(const ObjectLayer &layer);
	private:
	};
}

#endif

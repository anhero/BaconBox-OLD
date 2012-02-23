/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_GRAPHIC_TILE_MAP_LAYER_H
#define RB_GRAPHIC_TILE_MAP_LAYER_H

#include "Transformable.h"
#include "Layerable.h"

namespace RedBox {
	class GraphicTileLayer;
	class GraphicObjectLayer;

	/**
	 * Graphically represents a tile map layer. Graphic tile layers and graphic
	 * object layers are derived from this class.
	 * @ingroup TileMap
	 */
	class GraphicTileMapLayer : public Transformable, public Layerable {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param startingPosition Starting position of the graphic tile map
		 * layer.
		 */
		explicit GraphicTileMapLayer(const Vector2 &startingPosition = Vector2());

		/**
		 * Destructor.
		 */
		virtual ~GraphicTileMapLayer();

		/**
		 * Gets the instance as a graphic tile layer, if it is one.
		 * @return Pointer to the instance as a graphic tile layer if it is one.
		 * Null if not.
		 */
		virtual GraphicTileLayer *asTileLayer();

		/**
		 * Gets the instance as a graphic tile layer, if it is one.
		 * @return Pointer to the instance as a graphic tile layer if it is one.
		 * Null if not.
		 */
		virtual const GraphicTileLayer *asTileLayer() const;

		/**
		 * Gets the instance as a graphic object layer, if it is one.
		 * @return Pointer to the instance as a graphic object layer if it is
		 * one. Null if not.
		 */
		virtual GraphicObjectLayer *asObjectLayer();

		/**
		 * Gets the instance as a graphic object layer, if it is one.
		 * @return Pointer to the instance as a graphic object layer if it is
		 * one. Null if not.
		 */
		virtual const GraphicObjectLayer *asObjectLayer() const;
	};
}

#endif
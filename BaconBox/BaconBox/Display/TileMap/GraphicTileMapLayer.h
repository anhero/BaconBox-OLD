/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_GRAPHIC_TILE_MAP_LAYER_H
#define RB_GRAPHIC_TILE_MAP_LAYER_H

#include "Transformable.h"
#include "Layerable.h"

namespace BaconBox {
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
		 * Copy constructor.
		 * @param src Graphic tile map layer to make a copy of.
		 */
		GraphicTileMapLayer(const GraphicTileMapLayer &src);
		
		/**
		 * Destructor.
		 */
		virtual ~GraphicTileMapLayer();

		/**
		 * Assignment operator overload.
		 * @param src Graphic tile map layer to make a copy of.
		 * @return Reference to the graphic tile map layer.
		 */
		GraphicTileMapLayer &operator=(const GraphicTileMapLayer &src);
		
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
		
		/**
		 * Clones the instance of the graphic tile map layer.
		 * @return Duplicate of this graphic tile map layer. The caller is
		 * responsible for the ownership of this newly created batched tile.
		 */
		virtual GraphicTileMapLayer *clone() const = 0;
	};
}

#endif
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
	/**
	 * Graphically represents an object layer.
	 * @ingroup TileMap
	 */
	class GraphicObjectLayer : public GraphicTileMapLayer {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param startingPosition Starting position of the graphic object
		 * layer.
		 */
		explicit GraphicObjectLayer(const Vector2 &startingPosition = Vector2());
		
		/**
		 * Parameterized constructor.
		 * @param layer Object layer to initialize the graphic object layer 
		 * from.
		 * @param startingPosition Starting position of the graphic object
		 */
		explicit GraphicObjectLayer(const ObjectLayer &layer,
									const Vector2 &startingPosition = Vector2());
		
		/**
		 * Copy constructor.
		 * @param src Graphic object layer to make a copy of.
		 */
		GraphicObjectLayer(const GraphicObjectLayer &src);
		
		/**
		 * Destructor.
		 */
		~GraphicObjectLayer();
		
		/**
		 * Assignment operator overload.
		 * @param src Graphic object layer to copy.
		 * @return Reference to the modified instance.
		 */
		GraphicObjectLayer &operator=(const GraphicObjectLayer &src);

		/**
		 * Gets the instance as a graphic object layer, if it is one.
		 * @return Pointer to the instance as a graphic object layer if it is
		 * one. Null if not.
		 */
		GraphicObjectLayer *asObjectLayer();

		/**
		 * Gets the instance as a graphic object layer, if it is one.
		 * @return Pointer to the instance as a graphic object layer if it is
		 * one. Null if not.
		 */
		const GraphicObjectLayer *asObjectLayer() const;

		/**
		 * Clones the instance of the graphic tile map layer.
		 * @return Duplicate of this graphic tile map layer. The caller is
		 * responsible for the ownership of this newly created batched tile.
		 */
		GraphicObjectLayer *clone() const;

		/**
		 * Constructs the graphic object layer from an object layer.
		 * @param layer Object layer to load the graphic object layer from.
		 */
		void construct(const ObjectLayer &layer);
	private:
	};
}

#endif

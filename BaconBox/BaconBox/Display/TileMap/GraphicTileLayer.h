/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_GRAPHIC_TILE_LAYER_H
#define RB_GRAPHIC_TILE_LAYER_H

#include <map>

#include "BaconBox/Display/TileMap/GraphicTileMapLayer.h"
#include "BaconBox/Display/RenderBatch.h"
#include "BaconBox/Display/BatchedInanimateGraphicElement.h"
#include "BaconBox/Display/Collidable.h"

namespace BaconBox {
	class TileLayer;
	class CollisionGroup;
	/**
	 * Graphically represents a tile layer.
	 * @ingroup TileMap
	 */
	class GraphicTileLayer : public GraphicTileMapLayer {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param startingPosition Starting position of the graphic tile layer.
		 */
		explicit GraphicTileLayer(const Vector2 &startingPosition = Vector2());
		
		/**
		 * Parameterized constructor.
		 * @param layer Tile layer to initialize the graphic tile layer from.
		 * @param startingPosition Starting position of the graphic tile layer.
		 */
		explicit GraphicTileLayer(const TileLayer &layer,
								  const Vector2 &startingPosition = Vector2());

		/**
		 * Copy constructor.
		 * @param src Graphic tile layer to make a copy of.
		 */
		GraphicTileLayer(const GraphicTileLayer &src);

		/**
		 * Destructor.
		 */
		~GraphicTileLayer();

		/**
		 * Assignment operator overload.
		 * @param src Graphic tile layer to copy.
		 * @return Reference to the modified instance.
		 */
		GraphicTileLayer &operator=(const GraphicTileLayer &src);

		using GraphicTileMapLayer::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see BaconBox::Positionable::move(const Vector2& delta);
		 * @see BaconBox::Positionable::position
		 */
		void move(float xDelta, float yDelta);

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		using GraphicTileMapLayer::scaleFromPoint;

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see BaconBox::Transformable::scaling
		 */
		void scaleFromPoint(float xScaling, float yScaling,
		                    const Vector2 &fromPoint);

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see BaconBox::Transformable::angle
		 */
		void rotateFromPoint(float rotationAngle,
		                     const Vector2 &rotationPoint);

		/**
		 * Updates the body.
		 */
		void update();

		/**
		 * Renders the body in the context.
		 */
		void render();

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		void mask();

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		void unmask();

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		Maskable *getMask() const;

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		void setMask(Maskable *newMask, bool inverted = false);

		/**
		 * Gets the instance as a graphic tile layer, if it is one.
		 * @return Pointer to the instance as a graphic tile layer if it is one.
		 * Null if not.
		 */
		GraphicTileLayer *asTileLayer();

		/**
		 * Gets the instance as a graphic tile layer, if it is one.
		 * @return Pointer to the instance as a graphic tile layer if it is one.
		 * Null if not.
		 */
		const GraphicTileLayer *asTileLayer() const;

		/**
		 * Clones the instance of the graphic tile map layer.
		 * @return Duplicate of this graphic tile map layer. The caller is
		 * responsible for the ownership of this newly created batched tile.
		 */
		GraphicTileLayer *clone() const;

		/**
		 * Constructs the graphic tile layer from a tile layer.
		 * @param layer Tile layer to load the graphic tile layer from.
		 */
		void construct(const TileLayer &layer);

		void addToCollisionGroup(CollisionGroup &group);
	private:
		/// Map of batches by their tileset's texture.
		typedef std::map<TextureInformation *, RenderBatch<BatchedInanimateGraphicElement<Collidable> > *> BatchMap;

		/// Pointer to the current mask.
		Maskable *currentMask;

		/// Batches making up the graphic tile layer.
		BatchMap batches;
		
		void free();
		
		BatchMap::mapped_type getBatch(TextureInformation *textureInformation);
	};
}

#endif

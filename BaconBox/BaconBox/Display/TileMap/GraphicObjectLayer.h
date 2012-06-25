/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_GRAPHIC_OBJECT_LAYER_H
#define RB_GRAPHIC_OBJECT_LAYER_H

#include "GraphicTileMapLayer.h"
#include "GraphicElement.h"
#include "InanimateGraphicElement.h"
#include "SimpleBodyManager.h"
#include "Collidable.h"
#include "SimpleManageable.h"

namespace BaconBox {
	class ObjectLayer;
	/**
	 * Represents a graphic object layer in a graphic tile map.
	 * @ingroup TileMap
	 */
	class GraphicObjectLayer : public GraphicTileMapLayer {
	public:
		/// Type of container for the sprites.
		typedef SimpleBodyManager<GraphicElement<Collidable, SimpleManageable> > SpriteContainer;

		/// Type of container for the inanimate sprites.
		typedef SimpleBodyManager<InanimateGraphicElement<Collidable, SimpleManageable> > InanimateSpriteContainer;

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
		 * Gets the object layer's sprites.
		 * @return Reference to the container of sprites.
		 */
		SpriteContainer &getSprites();

		/**
		 * Gets the object layer's sprites.
		 * @return Const reference to the container of sprites.
		 */
		const SpriteContainer &getSprites() const;

		/**
		 * Gets the object layer's inanimate sprites.
		 * @return Reference to the container of inanimate sprites.
		 */
		InanimateSpriteContainer &getInanimateSprites();

		/**
		 * Gets the object layer's inanimate sprites.
		 * @return Const reference to the container of inanimate sprites.
		 */
		const InanimateSpriteContainer &getInanimateSprites() const;

		/**
		 * Constructs the graphic object layer from an object layer.
		 * @param layer Object layer to load the graphic object layer from.
		 */
		void construct(const ObjectLayer &layer);
	private:
		/// Pointer to the current mask.
		Maskable *currentMask;

		/// Sprites in the object layer.
		SpriteContainer sprites;

		/// Inanimate sprites in the object layer.
		InanimateSpriteContainer inanimateSprites;
	};
}

#endif

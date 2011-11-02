/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_SPRITE_H
#define RB_INANIMATE_SPRITE_H

#include "Inanimate.h"
#include "Graphic.h"
#include "Collidable.h"
#include "Layerable.h"
#include "TexturePointer.h"

namespace RedBox {
	class InanimateSprite : public Graphic<Inanimate>, public Collidable,
		public Layerable {
	public:
		/**
		 * Default constructor.
		 */
		InanimateSprite();

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the the full texture as the size and image.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit InanimateSprite(TexturePointer newTexture,
		                         const Vector2 &startingPosition = Vector2(),
		                         const Vector2 &newSize = Vector2(),
		                         const Vector2 &newTextureOffset = Vector2());

		/**
		 * Copy constructor.
		 * @param src InanimateSprite to make a copy of.
		 */
		InanimateSprite(const InanimateSprite &src);

		/**
		 * Destructor.
		 */
		virtual ~InanimateSprite();

		/**
		 * Assignment operator.
		 * @param src InanimateSprite to make a copy of.
		 * @return Reference to the modified InanimateSprite.
		 */
		InanimateSprite &operator=(const InanimateSprite &src);

		using Collidable::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see RedBox::Positionable::move(const Vector2& delta);
		 * @see RedBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta);

		/**
		 * Gets the geometric center of the body. Same as the position center
		 * in symmetrical polygons, but must be overloaded for classes that
		 * support irregular polygons.
		 * @return Geometric center of the body (barycenter).
		 */
		virtual const Vector2 getCentroid() const;

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		virtual const Vector2 getSize() const;

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const;

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const;

		using Collidable::scaleFromPoint;

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint);

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2 &rotationPoint);

		/**
		 * Generates the vertices and the texture coordinates for the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newPosition Position of the sprite in the world.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 */
		void construct(const Vector2 &newSize,
		               const Vector2 &newPosition,
		               const Vector2 &newTextureOffset = Vector2());
	};

}

#endif

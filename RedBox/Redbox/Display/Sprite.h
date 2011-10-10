/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include "Collidable.h"
#include "Layerable.h"
#include "Graphic.h"
#include "Animatable.h"

namespace RedBox {
	/**
     * Represents a sprite. A is used to display animated or non-animated
     * images or display colored shapes. To use a sprite, initialize it and
     * add it to a State. A sprite can only be in one state at a time. Once
     * you have given the pointer to the state, you don't have to worry about
     * deleting it, the state takes care of that for you. To remove a sprite
     * from a state, simply call setToBeDeleted(true), which is inherited from
     * Layerable.
     * @ingroup Display
     * @see RedBox::State
     */
class Sprite : public Graphic<Animatable>, public Collidable,
		public Layerable {
	public:
		/**
		 * Default constructor.
		 */
		Sprite();

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the the full texture as the size and image.
		 * @param newTextureKey Key to the texture to create a texturable from.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @param nbFrames Number of frames to load.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Sprite(const std::string &newTextureKey,
		                const Vector2 &startingPosition = Vector2(),
		                const Vector2 &newSize = Vector2(),
		                const Vector2 &newTextureOffset = Vector2(),
		                unsigned int nbFrames = 1);

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the the full texture as the size and image.
		 * @param newTextureInformation Pointer to the texture information to
		 * load the sprite with.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @param nbFrames Number of frames to load.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Sprite(const TextureInformation *newTextureInformation,
		                const Vector2 &startingPosition = Vector2(),
		                const Vector2 &newSize = Vector2(),
		                const Vector2 &newTextureOffset = Vector2(),
		                unsigned int nbFrames = 1);

		/**
		* Copy constructor.
		* @param src Sprite to make a copy of.
		*/
		Sprite(const Sprite &src);

		/**
		* Destructor.
		*/
		virtual ~Sprite();

		/**
		* Assignment operator.
		* @param src Sprite to make a copy of.
		* @return Reference to the modified Sprite.
		*/
		Sprite &operator=(const Sprite &src);

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
		 * Updates the body.
		 */
		virtual void update();

		/**
		 * Generates the vertices and the texture coordinates for the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newPosition Position of the sprite in the world.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @param nbFrames Number of frames to load.
		 */
		void construct(const Vector2 &newSize,
		               const Vector2 &newPosition,
		               const Vector2 &newTextureOffset = Vector2(),
		               unsigned int nbFrames = 1);
	};

}

#endif // RB_SPRITE_H

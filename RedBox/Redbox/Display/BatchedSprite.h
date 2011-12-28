/**
 * @file
 * @ingroup Display
 */
#ifndef RB_BATCHED_SPRITE_H
#define RB_BATCHED_SPRITE_H

#include "BatchedGraphic.h"
#include "Animatable.h"
#include "Collidable.h"
#include "BatchedBody.h"

namespace RedBox {
	template <typename T> class RenderBatch;
	class BatchedSprite : public BatchedGraphic<Animatable, BatchedSprite>,
		public Collidable, public BatchedBody {
		template <typename V> friend class RenderBatch;
	public:
		/**
		 * Default constructor.
		 */
		BatchedSprite();

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the the full texture as the size and image.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @param nbFrames Number of frames to load.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit BatchedSprite(TexturePointer newTexture,
		                       const Vector2 &startingPosition = Vector2(),
		                       const Vector2 &newSize = Vector2(),
		                       const Vector2 &newTextureOffset = Vector2(),
		                       unsigned int nbFrames = 1);

		/**
		 * Copy constructor.
		 * @param src Batched sprite to make a copy of.
		 */
		BatchedSprite(const BatchedSprite &src);

		/**
		 * Destructor.
		 */
		virtual ~BatchedSprite();

		/**
		 * Assignation operator overload.
		 * @param src Batched sprite to make a copy of.
		 * @return Batched sprite resulting of the copy.
		 */
		BatchedSprite &operator=(const BatchedSprite &src);

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
		/**
		 * Clones the current batched sprite.
		 * @return Pointer to the new allocated batched sprite.
		 */
		BatchedSprite *clone() const;
	private:

		/**
		 * Parameterized constructor. Used internally by the render batch.
		 * @param newBatch Pointer to the parent batch.
		 * @param newVertices Pointer to the array of vertices to use. The
		 * sprite's vertex array will manage this pointer.
		 */
		BatchedSprite(RenderBatch<BatchedSprite> *newBatch,
		              BatchedVertexArray<BatchedSprite>::ContainerType *newVertices);

		/**
		 * Paremeterized constructor. Used internally by the render batch.
		 * @param newBatch Pointer to the parent batch.
		 * @param newBegin Index in the batch's array where the sprite's
		 * vertices begin.
		 * @param newNbVertices Number of vertices the sprite has.
		 */
		BatchedSprite(RenderBatch<BatchedSprite> *newBatch,
		              BatchedVertexArray<BatchedSprite>::SizeType newBegin,
		              BatchedVertexArray<BatchedSprite>::SizeType newNbVertices);
	};

}

#endif // RB_BATCHED_SPRITE_H

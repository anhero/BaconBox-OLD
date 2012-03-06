/**
 * @file
 * @ingroup Display
 */
#ifndef RB_BATCHED_INANIMATE_GRAPHIC_ELEMENT_H
#define RB_BATCHED_INANIMATE_GRAPHIC_ELEMENT_H

#include "BatchedGraphic.h"
#include "Inanimate.h"
#include "BatchedBody.h"
#include "ShapeFactory.h"
#include "TextureInformation.h"
#include "CallHelper.h"
#include "IsBaseOf.h"
#include "StaticAssert.h"
#include "IsSame.h"
#include "Transformable.h"

namespace RedBox {
	/**
	 * Represents a batched inanimate graphic element. Can be initialized and
	 * manipulated while out of a sprite batch, but must be part of a batch to
	 * be rendered.
	 * @tparam Parent Either Transformable or Collidable.
	 * @ingroup Display
	 */
	template <typename Parent>
	class BatchedInanimateGraphicElement :
		public BatchedGraphic<Inanimate, BatchedInanimateGraphicElement<Parent> >,
		public Parent, public BatchedBody {
		template <typename T> friend class RenderBatchParent;
		template <typename T, bool ANIMATABLE> friend class RenderBatchMiddle;
	public:
		/**
		 * Default constructor.
		 */
		BatchedInanimateGraphicElement() :
			BatchedGraphic<Inanimate, BatchedInanimateGraphicElement<Parent> >(),
			Parent(), BatchedBody() {
		}

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the full texture as the size and image.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param newSize Size of the sprite.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit BatchedInanimateGraphicElement(TexturePointer newTexture,
		                                        const Vector2 &startingPosition = Vector2(),
		                                        const Vector2 &newSize = Vector2(),
		                                        const Vector2 &newTextureOffset = Vector2()) :
			BatchedGraphic<Inanimate, BatchedInanimateGraphicElement<Parent> >(newTexture),
			Parent(startingPosition) {
			// We check if we have to use the texture as the full image.
			if (newSize.x <= 0.0f || newSize.y <= 0.0f) {
				// We make sure the texture information is valid.
				if (this->getTextureInformation()) {
					construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth),
					                  static_cast<float>(this->getTextureInformation()->imageHeight)),
					          startingPosition);
				}

			} else {
				construct(newSize, startingPosition, newTextureOffset);
			}
		}

		/**
		 * Copy constructor.
		 * @param src Batched inanimate sprite to make a copy of.
		 */
		BatchedInanimateGraphicElement(const BatchedInanimateGraphicElement<Parent> &src) :
			BatchedGraphic<Inanimate, BatchedInanimateGraphicElement<Parent> >(src),
			Parent(src), BatchedBody(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~BatchedInanimateGraphicElement() {
		}

		/**
		 * Assignation operator overload.
		 * @param src Batched inanimate sprite to make a copy of.
		 * @return Batched inanimate sprite resulting of the copy.
		 */
		BatchedInanimateGraphicElement<Parent> &operator=(const BatchedInanimateGraphicElement<Parent> &src) {
			this->BatchedGraphic<Inanimate, BatchedInanimateGraphicElement<Parent> >::operator=(src);
			this->Parent::operator=(src);
			this->BatchedBody::operator=(src);
			return *this;
		}

		using Parent::move;

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
		virtual void move(float xDelta, float yDelta) {
			this->Parent::move(xDelta, yDelta);
			this->getVertices().move(xDelta, yDelta);
		}

		/**
		 * Gets the geometric center of the body. Same as the position center
		 * in symmetrical polygons, but must be overloaded for classes that
		 * support irregular polygons.
		 * @return Geometric center of the body (barycenter).
		 */
		virtual const Vector2 getCentroid() const {
			return this->getVertices().getCentroid();
		}

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		virtual const Vector2 getSize() const {
			return this->getVertices().getSize();
		}

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const {
			return this->getVertices().getWidth();
		}

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const {
			return this->getVertices().getHeight();
		}

		using Parent::scaleFromPoint;

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
		                            const Vector2 &fromPoint) {
			this->Parent::scaleFromPoint(xScaling, yScaling, fromPoint);
			this->getVertices().scaleFromPoint(xScaling, yScaling, fromPoint);
			Vector2 tmpPosition = this->getVertices().getMinimumXY();
			this->Parent::move(tmpPosition.x - this->getXPosition(),
			                   tmpPosition.y - this->getYPosition());
		}

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2 &rotationPoint) {
			this->Parent::rotateFromPoint(rotationAngle, rotationPoint);
			this->getVertices().rotateFromPoint(rotationAngle, rotationPoint);
			Vector2 tmpPosition = this->getVertices().getMinimumXY();
			this->Parent::move(tmpPosition.x - this->getXPosition(),
			                   tmpPosition.y - this->getYPosition());
		}

		/**
		 * Updates the body.
		 */
		virtual void update() {
			CallUpdate<BatchedInanimateGraphicElement<Parent>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);
		}

		/**
		 * Generates the vertices and the texture coordinates for the
		 * inanimate sprite.
		 * @param newSize Size of the sprite.
		 * @param newPosition Position of the sprite in the world.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 */
		void construct(const Vector2 &newSize,
		               const Vector2 &newPosition,
		               const Vector2 &newTextureOffset = Vector2()) {
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(newSize, newPosition, &this->getVertices());

			// We check if we have to initialize the texture coordinates.
			if (this->getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), newTextureOffset);
			}

			this->refreshTextureCoordinates();
		}

		/**
		 * Clones the current batched sprite.
		 * @return Pointer to the new allocated batched sprite.
		 */
		virtual BatchedInanimateGraphicElement<Parent> *clone() const {
			return new BatchedInanimateGraphicElement<Parent>(*this);
		}
	private:
		/// Makes sure the parent type is at least transformable.
		typedef typename StaticAssert < IsBaseOf<Transformable, Parent>::RESULT || IsSame<Transformable, Parent>::RESULT >::Result IsParentTransformable;

		/**
		 * Parameterized constructor. Used internally by the render batch.
		 * @param newBatch Pointer to the parent batch.
		 * @param newVertices Pointer to the array of vertices to use. The
		 * sprite's vertex array will manage this pointer.
		 * @param src Other batched inanimate graphic element from which to
		 * base the initial values.
		 */
		BatchedInanimateGraphicElement(RenderBatch<BatchedInanimateGraphicElement<Parent> > *newBatch,
		                               typename BatchedVertexArray<BatchedInanimateGraphicElement<Parent> >::ContainerType *newVertices,
		                               const BatchedInanimateGraphicElement<Parent> &src) :
			BatchedGraphic<Animatable, BatchedInanimateGraphicElement<Parent> >(newBatch, newVertices, src),
			Parent(src), BatchedBody(src) {
		}

		/**
		 * Paremeterized constructor. Used internally by the render batch.
		 * @param newBatch Pointer to the parent batch.
		 * @param newBegin Index in the batch's array where the sprite's
		 * vertices begin.
		 * @param newNbVertices Number of vertices the sprite has.
		 * @param src Other batched inanimate graphic element from which to
		 * base the initial values.
		 */
		BatchedInanimateGraphicElement(RenderBatch<BatchedInanimateGraphicElement<Parent> > *newBatch,
		                               typename BatchedVertexArray<BatchedInanimateGraphicElement<Parent> >::SizeType newBegin,
		                               typename BatchedVertexArray<BatchedInanimateGraphicElement<Parent> >::SizeType newNbVertices,
		                               const BatchedInanimateGraphicElement<Parent> &src) :
			BatchedGraphic<Animatable, BatchedInanimateGraphicElement<Parent> >(newBatch, newBegin, newNbVertices, src),
			Parent(src), BatchedBody(src) {
		}
	};
}

#endif // RB_BATCHED_INANIMATE_GRAPHIC_ELEMENT_H

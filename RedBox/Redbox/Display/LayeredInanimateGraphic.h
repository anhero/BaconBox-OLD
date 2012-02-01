/**
 * @file
 * @ingroup Display
 */
#ifndef RB_LAYERED_INANIMATE_GRAPHIC_H
#define RB_LAYERED_INANIMATE_GRAPHIC_H

#include "Inanimate.h"
#include "Graphic.h"
#include "Layerable.h"
#include "TexturePointer.h"
#include "ShapeFactory.h"
#include "TextureInformation.h"
#include "CallHelper.h"
#include "IsBaseOf.h"

namespace RedBox {
	/**
	 * Represents an inanimate graphic that can be added to a state (because it
	 * is layered). It can be Collidable or only Transformable.
	 * @tparam Parent Either Transformable or Collidable.
	 * @ingroup Display
	 * @see RedBox::Sprite
	 */
	template <typename Parent>
	class LayeredInanimateGraphic : public Graphic<Inanimate>, public Parent,
		public Layerable {
	public:
		/**
		 * Default constructor.
		 */
		LayeredInanimateGraphic() : Graphic<Inanimate>(), Parent(),
			Layerable() {
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
		explicit LayeredInanimateGraphic(TexturePointer newTexture,
		                                 const Vector2 &startingPosition = Vector2(),
		                                 const Vector2 &newSize = Vector2(),
		                                 const Vector2 &newTextureOffset = Vector2()) :
			Graphic<Inanimate>(newTexture), Parent(startingPosition),
			Layerable() {
			// We check if we have to use the texture as the full image.
			if (newSize.getX() <= 0.0f || newSize.getY() <= 0.0f) {
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
		 * @param src Layered inanimate graphic to make a copy of.
		 */
		LayeredInanimateGraphic(const LayeredInanimateGraphic<Parent> &src) :
			Graphic<Inanimate>(src), Parent(src), Layerable(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~LayeredInanimateGraphic() {
		}

		/**
		 * Assignment operator.
		 * @param src Layered inanimate graphic to copy.
		 * @return Reference to the modified layered inanimate graphic.
		 */
		LayeredInanimateGraphic &operator=(const LayeredInanimateGraphic<Parent> &src) {
			this->Graphic<Inanimate>::operator=(src);
			this->Parent::operator=(src);
			this->Layerable::operator=(src);
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
			this->Parent::move(tmpPosition.getX() - this->getXPosition(),
			                   tmpPosition.getY() - this->getYPosition());
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
			this->Parent::move(tmpPosition.getX() - this->getXPosition(),
			                   tmpPosition.getY() - this->getYPosition());
		}

		/**
		 * Updates the body.
		 */
		virtual void update() {
			// We call the parent update method if the Parent template parameter
			// implements it.
			CallUpdate<LayeredInanimateGraphic<Parent>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);
		}

		/**
		 * Generates the vertices and the texture coordinates for the
		 * sprite.
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
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);

			// We check if we have to initialize the texture coordinates.
			if (this->getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), newTextureOffset);

				// We make sure the texture coordinates were loaded correctly.
				if (this->getCurrentTextureCoordinates().size() == this->getVertices().getNbVertices()) {
					this->addRenderMode(RenderMode::TEXTURE);
				}

			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}
		}
	};
}

#endif

/**
 * @file
 */
#ifndef RB_INANIMATE_GRAPHIC_ELEMENT_H
#define RB_INANIMATE_GRAPHIC_ELEMENT_H

#include "Transformable.h"
#include "Inanimate.h"
#include "Graphic.h"
#include "TextureInformation.h"
#include "ShapeFactory.h"
#include "StaticAssert.h"
#include "IsBaseOf.h"
#include "IsSame.h"
#include "TexturePointer.h"

namespace RedBox {
	/**
	 * Graphic element that cannot be animated, just like the inanimate sprite,
	 * but not layerable and can be collidable or only transformable (collidable means
	 * it is also transformable).
	 * @tparam Parent Collidable or Transformable.
	 * @ingroup Display
	 */
	template <typename Parent>
	class InanimateGraphicElement : public Graphic<Inanimate>,
		public Parent {
	public:
		/**
		 * Default constructor.
		 */
		InanimateGraphicElement() : Graphic<Inanimate>(),
			Parent() {
		}

		/**
		 * Parameterized constructor. Loads the vertices and the texture
		 * coordinates. If the specified size has a coordinate equal to 0 or
		 * lower, it loads the the full texture as the size and image.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * graphic element.
		 * @param newSize Size of the graphic element.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit InanimateGraphicElement(TexturePointer newTexture,
		                                 const Vector2 &startingPosition = Vector2(),
		                                 const Vector2 &newSize = Vector2(),
		                                 const Vector2 &newTextureOffset = Vector2()) :
			Graphic<Inanimate>(newTexture), Parent(startingPosition) {
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
		 * @param src InanimateGraphicElement to make a copy of.
		 */
		InanimateGraphicElement(const InanimateGraphicElement &src) :
			Graphic<Inanimate>(src), Parent(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~InanimateGraphicElement() {
		}

		/**
		 * Assignment operator.
		 * @param src InanimateGraphicElement to make a copy of.
		 * @return Reference to the modified InanimateGraphicElement.
		 */
		InanimateGraphicElement &operator=(const InanimateGraphicElement &src) {
			this->Graphic<Inanimate>::operator=(src);
			this->Parent::operator=(src);
			return *this;
		}

		using Transformable::move;

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
			getVertices().move(xDelta, yDelta);
		}

		/**
		 * Gets the geometric center of the body. Same as the position center
		 * in symmetrical polygons, but must be overloaded for classes that
		 * support irregular polygons.
		 * @return Geometric center of the body (barycenter).
		 */
		virtual const Vector2 getCentroid() const {
			return getVertices().getCentroid();
		}

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		virtual const Vector2 getSize() const {
			return getVertices().getSize();
		}

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const {
			return getVertices().getWidth();
		}

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const {
			return getVertices().getHeight();
		}

		using Transformable::scaleFromPoint;

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
			getVertices().scaleFromPoint(xScaling, yScaling, fromPoint);
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
			getVertices().rotateFromPoint(rotationAngle, rotationPoint);
			Vector2 tmpPosition = this->getVertices().getMinimumXY();
			this->Parent::move(tmpPosition.getX() - this->getXPosition(),
			                   tmpPosition.getY() - this->getYPosition());
		}

		/**
		 * Generates the vertices and the texture coordinates for the
		 * graphic element.
		 * @param newSize Size of the graphic element.
		 * @param newPosition Position of the graphic element in the world.
		 * @param newTextureOffset Texture coordinates' offset if needed.
		 */
		void construct(const Vector2 &newSize,
		               const Vector2 &newPosition,
		               const Vector2 &newTextureOffset = Vector2()) {
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(newSize, newPosition, &this->getVertices());
			// We specify the render mode.
			addRenderMode(RenderMode::SHAPE);
			addRenderMode(RenderMode::COLOR);

			// We check if we have to initialize the texture coordinates.
			if (getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), newTextureOffset);

				// We make sure the texture coordinates were loaded correctly.
				if (getCurrentTextureCoordinates().size() == this->getVertices().getNbVertices()) {
					addRenderMode(RenderMode::TEXTURE);
				}

			} else {
				removeRenderMode(RenderMode::TEXTURE);
			}
		}
	private:
		/// Makes sure the parent type is at least transformable.
		typedef typename StaticAssert < IsBaseOf<Transformable, Parent>::RESULT || IsSame<Transformable, Parent>::RESULT >::Result IsParentTransformable;
	};

}

#endif // RB_INANIMATE_GRAPHIC_ELEMENT_H

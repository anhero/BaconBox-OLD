#ifndef RB_LAYERED_GRAPHIC_H
#define RB_LAYERED_GRAPHIC_H

#include "Layerable.h"
#include "Graphic.h"
#include "Animatable.h"
#include "TexturePointer.h"
#include "ShapeFactory.h"
#include "TextureInformation.h"
#include "SpriteDefinition.h"
#include "Console.h"
#include "CallHelper.h"
#include "IsBaseOf.h"

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
	template <typename Parent>
	class LayeredGraphic : public Graphic<Animatable>, public Parent,
		public Layerable {
	public:
		/**
		 * Default constructor.
		 */
		LayeredGraphic() : Graphic<Animatable>(), Parent(), Layerable() {
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
		 * @param nbFrames Number of frames to load. If set to 0, it will use the maximum frame number
		 * for the texture and size of the Animatable object.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit LayeredGraphic(TexturePointer newTexture,
		                        const Vector2 &startingPosition = Vector2(),
		                        const Vector2 &newSize = Vector2(),
		                        const Vector2 &newTextureOffset = Vector2(),
		                        unsigned int nbFrames = 1) :
			Graphic<Animatable>(newTexture), Parent(startingPosition),
			Layerable() {
			// We check if we have to use the texture as the full image.
			if (newSize.getX() <= 0.0f || newSize.getY() <= 0.0f) {
				// We make sure the texture information is valid.
				if (this->getTextureInformation()) {
					construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth),
					                  static_cast<float>(this->getTextureInformation()->imageHeight)),
					          startingPosition);

				} else {
					Console::println("Failed to load the sprite because the texture is NULL.");
				}

			} else {
				construct(newSize, startingPosition, newTextureOffset, nbFrames);
			}
		}

		/**
		 * Parameterized constructor. Loads the sprite from a sprite definition.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 * @param definition Information about the sprite's shape, its frames
		 * and its animations.
		 */
		LayeredGraphic(TexturePointer newTexture,
		               const SpriteDefinition &definition,
		               const Vector2 &startingPosition = Vector2()) :
			Graphic<Animatable>(newTexture), Parent(startingPosition),
			Layerable() {
			// We make sure the texture information is valid.
			if (this->getTextureInformation()) {
				construct(definition);
				this->getVertices().move(startingPosition.getX(), startingPosition.getY());

			} else {
				Console::println("Failed to load the sprite because the texture is NULL.");
			}
		}

		/**
		* Copy constructor.
		* @param src Sprite to make a copy of.
		*/
		LayeredGraphic(const LayeredGraphic<Parent> &src) : Graphic<Animatable>(src),
			Parent(src), Layerable(src) {
		}

		/**
		* Destructor.
		*/
		virtual ~LayeredGraphic() {
		}

		/**
		* Assignment operator.
		* @param src Sprite to make a copy of.
		* @return Reference to the modified Sprite.
		*/
		LayeredGraphic<Parent> &operator=(const LayeredGraphic<Parent> &src) {
			this->Graphic<Animatable>::operator=(src);
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
			CallUpdate<LayeredGraphic<Parent>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);
			this->Graphic<Animatable>::update();
		}

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
		               unsigned int nbFrames = 1) {

			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(newSize, newPosition,
			                              &this->getVertices());
			// We specify the render modes.
			addRenderMode(RenderMode::SHAPE);
			addRenderMode(RenderMode::COLOR);

			// We check if we have to initialize the texture coordinates.
			if (getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), newTextureOffset,
				                       nbFrames);

				// We make sure the texture coordinates were loaded correctly.
				if (this->getCurrentTextureCoordinates().size() == this->getVertices().getNbVertices()) {
					addRenderMode(RenderMode::TEXTURE);
				}

			} else {
				removeRenderMode(RenderMode::TEXTURE);
			}
		}

		/**
		 * Generates teh vertices and the texture coordinates from a sprite
		 * definition.
		 * @param definition Sprite definition containing the necessary details.
		 */
		void construct(const SpriteDefinition &definition) {
			// We initialize the vertices.
			this->getVertices() = definition.vertices;

			// We specify the render modes.
			addRenderMode(RenderMode::SHAPE);
			addRenderMode(RenderMode::COLOR);

			// We check if we have to initialize the texture coordinates.
			if (getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), definition.frames);

				// We add the animations to the sprite.
				this->clearAnimations();

				for (AnimationMap::const_iterator i = definition.animations.begin();
				     i != definition.animations.end(); ++i) {
					this->addAnimation(i->first, i->second);
				}

				addRenderMode(RenderMode::TEXTURE);
			}
		}
	};
}

#endif

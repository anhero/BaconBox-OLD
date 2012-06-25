/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_GRAPHIC_ELEMENT_H
#define RB_INANIMATE_GRAPHIC_ELEMENT_H

#include "Inanimate.h"
#include "Graphic.h"
#include "Transformable.h"
#include "TexturePointer.h"
#include "ShapeFactory.h"
#include "TextureInformation.h"
#include "CallHelper.h"
#include "IsBaseOf.h"
#include "IsSame.h"
#include "StaticAssert.h"
#include "TileObject.h"
#include "RectangleObject.h"
#include "PolygonObject.h"
#include "TileMap.h"
#include "ObjectLayer.h"
#include "Tileset.h"
#include "TileMapUtility.h"
#include "FrameDetails.h"
#include "AlgorithmHelper.h"
#include "FrameDetails.h"
#include "Manageable.h"
#include "NonManageable.h"

namespace BaconBox {
	/**
	 * Represents an inanimate graphic that can be added to a state (because it
	 * is layered). It can be Collidable or only Transformable.
	 * @tparam Parent Either Transformable or Collidable.
	 * @ingroup Display
	 * @see BaconBox::Sprite
	 */
	template <typename Parent, typename ManageParent = NonManageable>
	class InanimateGraphicElement : public Graphic<Inanimate>, public Parent,
		public ManageParent {
	public:
		/**
		 * Default constructor.
		 */
		InanimateGraphicElement() : Graphic<Inanimate>(), Parent(),
			ManageParent() {
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
		 * @see BaconBox::Texturable::textureInformation
		 */
		explicit InanimateGraphicElement(TexturePointer newTexture,
		                                 const Vector2 &startingPosition = Vector2(),
		                                 const Vector2 &newSize = Vector2(),
		                                 const Vector2 &newTextureOffset = Vector2()) :
			Graphic<Inanimate>(newTexture), Parent(startingPosition),
			ManageParent() {
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
		 * @param src Layered inanimate graphic to make a copy of.
		 */
		InanimateGraphicElement(const InanimateGraphicElement<Parent, ManageParent> &src) :
			Graphic<Inanimate>(src), Parent(src), ManageParent(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~InanimateGraphicElement() {
		}

		/**
		 * Assignment operator.
		 * @param src Layered inanimate graphic to copy.
		 * @return Reference to the modified layered inanimate graphic.
		 */
		InanimateGraphicElement<Parent, ManageParent> &operator=(const InanimateGraphicElement<Parent, ManageParent> &src) {
			this->Graphic<Inanimate>::operator=(src);
			this->Parent::operator=(src);
			this->ManageParent::operator=(src);
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
		 * @see BaconBox::Positionable::move(const Vector2& delta);
		 * @see BaconBox::Positionable::position
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
		 * @see BaconBox::Transformable::scaling
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
		 * @see BaconBox::Transformable::angle
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
			// We call the parent update method if the Parent template parameter
			// implements it.
			CallUpdate<InanimateGraphicElement<Parent, ManageParent>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);
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
			this->construct(newSize, newPosition, FrameDetails(newTextureOffset, FrameDetails::Orientation::NORTH));
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
		               const FrameDetails &frameDetails) {
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(newSize, newPosition, &this->getVertices());
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);

			// We check if we have to initialize the texture coordinates.
			if (this->getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), frameDetails);

				// We make sure the texture coordinates were loaded correctly.
				if (this->getCurrentTextureCoordinates().size() == this->getVertices().getNbVertices()) {
					this->addRenderMode(RenderMode::TEXTURE);
				}

			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}
		}

		/**
		 * Constructs the layered inanimate graphic from a tile object.
		 * @param tile Tile object to construct the layered inanimate graphic
		 * from.
		 */
		virtual void construct(const TileObject &tile) {
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(tile.getSize(), tile.getPosition() - tile.getHeight(), &this->getVertices());
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);

			// We get the texture and the texture coordinates.
			const Tileset *tileset = tile.parentLayer.parentMap.getTileset(tile.getTileId());

			if (tileset) {
				if (tileset->loadTextureCoordinates(tile.getTileId(),
				                                    this->getTextureCoordinates()) &&
				    this->getCurrentTextureCoordinates().size() == this->getVertices().getNbVertices()) {
					this->setTextureInformation(tileset->getTextureInformation());
					this->addRenderMode(RenderMode::TEXTURE);
				}

			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}

			// We get the tile's color.
			this->setColor(TileMapUtility::readColor(tile.getProperties()));

			loadCollidableProperties(tile.getProperties());
		}

		/**
		 * Constructs the layered inanimate graphic from a tile object.
		 * @param rectangle Rectangle object to construct the layered inanimate
		 * graphic from.
		 */
		virtual void construct(const RectangleObject &rectangle) {
			this->setTextureInformation(TileMapUtility::readTextureKey(rectangle.getProperties()));
			this->Parent::move(rectangle.getXPosition() - this->getXPosition(),
			                   rectangle.getYPosition() - this->getYPosition());
			this->construct(rectangle.getSize(), this->getPosition(),
			                TileMapUtility::readFrame(rectangle.getProperties()));

			// We read the rectangle's color.
			this->setColor(TileMapUtility::readColor(rectangle.getProperties()));

			loadCollidableProperties(rectangle.getProperties());
		}

		/**
		 * Construcs the layered inanimate graphic from a tile object.
		 * @param polygon Polygon object to construct the layered inanimate
		 * graphic from. We assume that the polygon is convex, else it might
		 * display incorrectly.
		 */
		virtual void construct(const PolygonObject &polygon) {
			this->setTextureInformation(TileMapUtility::readTextureKey(polygon.getProperties()));
			this->Parent::move(polygon.getXPosition() - this->getXPosition(),
			                       polygon.getYPosition() - this->getYPosition());
			this->getVertices() = polygon.getVertices();
			// We sort the vertices to be in the right order for triangle
			// strips. We assume the shape is convex.
			AlgorithmHelper::riffleShuffle(this->getVertices().getBegin(),
			                               this->getVertices().getEnd());

			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);

			// We check if we have to initialize the texture coordinates.
			if (this->getTextureInformation()) {
				this->loadTextureCoordinates(this->getVertices(), TileMapUtility::readFrame(polygon.getProperties()));

				// We make sure the texture coordinates were loaded correctly.
				if (this->getCurrentTextureCoordinates().size() == this->getVertices().getNbVertices()) {
					this->addRenderMode(RenderMode::TEXTURE);
				}

			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}

			// We read the polygon's color.
			this->setColor(TileMapUtility::readColor(polygon.getProperties()));

			loadCollidableProperties(polygon.getProperties());
		}

		/**
		 * Gets a duplicate of the layered graphic.
		 * @return Pointer to a duplicate of the layered graphic. The caller is
		 * responsible for deleting this instance.
		 */
		virtual InanimateGraphicElement<Parent, ManageParent> *clone() const {
			return new InanimateGraphicElement<Parent, ManageParent>(*this);
		}
	private:
		/// Makes sure the parent type is at least transformable.
		typedef typename StaticAssert < IsBaseOf<Transformable, Parent>::RESULT || IsSame<Transformable, Parent>::RESULT >::Result IsParentTransformable;

		/// Makes sure the manage parent type is at least manageable.
		typedef typename StaticAssert < IsBaseOf<Manageable, ManageParent>::RESULT || IsSame<Manageable, ManageParent>::RESULT || IsSame<NonManageable, ManageParent>::RESULT >::Result IsManageParentManageable;

		/**
		 * Loads the properties of a collidable if we are derived from
		 * Collidable.
		 */
		void loadCollidableProperties(const PropertyMap &properties) {
			CallLoadCollidable<InanimateGraphicElement<Parent, ManageParent>, IsBaseOf<Collidable, InanimateGraphicElement<Parent, ManageParent> >::RESULT>()(properties, *this);
		}
	};
}

#endif

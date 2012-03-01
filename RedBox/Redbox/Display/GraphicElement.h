/**
 * @file
 * @ingroup Display
 */
#ifndef RB_GRAPHIC_ELEMENT_H
#define RB_GRAPHIC_ELEMENT_H

#include "Graphic.h"
#include "Animatable.h"
#include "Transformable.h"
#include "TexturePointer.h"
#include "ShapeFactory.h"
#include "TextureInformation.h"
#include "SpriteDefinition.h"
#include "Console.h"
#include "CallHelper.h"
#include "IsBaseOf.h"
#include "StaticAssert.h"
#include "IsSame.h"
#include "TileObject.h"
#include "RectangleObject.h"
#include "PolygonObject.h"
#include "TileMap.h"
#include "ObjectLayer.h"
#include "Tileset.h"
#include "TileMapUtility.h"
#include "FrameDetails.h"
#include "AlgorithmHelper.h"
#include "FrameArray.h"
#include "Manageable.h"
#include "NonManageable.h"

namespace RedBox {
	/**
	 * Represents a sprite. A is used to display animated or non-animated
	 * images or display colored shapes. To use a sprite, initialize it and
	 * add it to a State. A sprite can only be in one state at a time. Once
	 * you have given the pointer to the state, you don't have to worry about
	 * deleting it, the state takes care of that for you. To remove a sprite
	 * from a state, simply call setToBeDeleted(true), which is inherited from
	 * Manageable.
	 * @tparam Parent Either Transformable or Collidable.
	 * @tparam ManageParent NonManageable, Manageable or a class derived from
	 * Manageable.
	 * @ingroup Display
	 * @see RedBox::State
	 */
	template <typename Parent, typename ManageParent = NonManageable>
	class GraphicElement : public Graphic<Animatable>, public Parent,
	public ManageParent {
	public:
		/**
		 * Default constructor.
		 */
		GraphicElement() : Graphic<Animatable>(), Parent(), ManageParent() {
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
		explicit GraphicElement(TexturePointer newTexture,
		                        const Vector2 &startingPosition = Vector2(),
		                        const Vector2 &newSize = Vector2(),
		                        const Vector2 &newTextureOffset = Vector2(),
		                        unsigned int nbFrames = 1) :
		Graphic<Animatable>(newTexture), Parent(startingPosition),
		ManageParent() {
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
		 * @param definition Information about the sprite's shape, its frames
		 * and its animations.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 */
		GraphicElement(TexturePointer newTexture,
		               const SpriteDefinition &definition,
		               const Vector2 &startingPosition = Vector2()) :
		Graphic<Animatable>(newTexture), Parent(startingPosition),
		ManageParent() {
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
		 * @param src Managed graphic to make a copy of.
		 */
		GraphicElement(const GraphicElement<Parent, ManageParent> &src) : Graphic<Animatable>(src),
		Parent(src), ManageParent(src) {
		}
		
		/**
		 * Destructor.
		 */
		virtual ~GraphicElement() {
		}
		
		/**
		 * Assignment operator.
		 * @param src Managed graphic to copy.
		 * @return Reference to the modified managed graphic.
		 */
		GraphicElement<Parent, ManageParent> &operator=(const GraphicElement<Parent, ManageParent> &src) {
			this->Graphic<Animatable>::operator=(src);
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
			CallUpdate<GraphicElement<Parent, ManageParent>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);
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
		
		void construct(const Vector2 &newSize,
		               const Vector2 &newPosition,
		               const FrameDetails &frameDetails) {
			
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(newSize, newPosition,
			                              &this->getVertices());
			// We specify the render modes.
			addRenderMode(RenderMode::SHAPE);
			addRenderMode(RenderMode::COLOR);
			
			// We check if we have to initialize the texture coordinates.
			if (getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), FrameArray(1, frameDetails));
				
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
		
		/**
		 * Constructs the managed graphic from a tile object.
		 * @param tile Tile object to construct the managed graphic from.
		 */
		virtual void construct(const TileObject &tile) {
			this->clearAnimations();
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(tile.getSize(), tile.getPosition() - tile.getHeight(), &this->getVertices());
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);
			
			// We get the texture and the texture coordinates.
			const Tileset *tileset = tile.parentLayer.parentMap.getTileset(tile.getTileId());
			
			if (tileset) {
				this->getFrames().resize(1);
				
				if (tileset->loadTextureCoordinates(tile.getTileId(),
				                                    this->getFrames()[0]) &&
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
		 * Constructs the managed graphic from a rectangle object.
		 * @param rectangle Rectangle object to construct the managed graphic
		 * from.
		 */
		virtual void construct(const RectangleObject &rectangle) {
			this->clearAnimations();
			this->setTextureInformation(TileMapUtility::readTextureKey(rectangle.getProperties()));
			this->Parent::move(rectangle.getXPosition() - this->getXPosition(),
			                   rectangle.getYPosition() - this->getYPosition());
			
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(rectangle.getSize(),
			                              rectangle.getPosition(), &this->getVertices());
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);
			
			// We check if we have to initialize the texture coordinates.
			if (this->getTextureInformation()) {
				// We load the texture coordinates.
				FrameArray newFrames;
				TileMapUtility::readFrames(rectangle.getProperties(),
				                           newFrames);
				
				this->loadTextureCoordinates(this->getVertices(),
				                             newFrames);
				
				this->addRenderMode(RenderMode::TEXTURE);
				
				// We load the animations.
				TileMapUtility::readAnimations(rectangle.getProperties(),
				                               *this);
				
				// We set the default frame.
				this->setDefaultFrame(TileMapUtility::readDefaultFrame(rectangle.getProperties()));
				
				// We start the default animation.
				this->startAnimation(TileMapUtility::readDefaultAnimation(rectangle.getProperties()));
				
			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}
			
			
			// We read the rectangle's color.
			this->setColor(TileMapUtility::readColor(rectangle.getProperties()));
			
			loadCollidableProperties(rectangle.getProperties());
		}
		
		/**
		 * Constructs the managed graphic from a polygon object.
		 * @param polygon Polygon object to construct the managed graphic from.
		 */
		virtual void construct(const PolygonObject &polygon) {
			this->clearAnimations();
			this->setTextureInformation(TileMapUtility::readTextureKey(polygon.getProperties()));
			this->Parent::move(polygon.getXPosition() - this->getXPosition(),
			                   polygon.getYPosition() - this->getYPosition());
			
			// We initialize the vertices.
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
				// We load the texture coordinates.
				FrameArray newFrames;
				TileMapUtility::readFrames(polygon.getProperties(),
				                           newFrames);
				
				this->loadTextureCoordinates(this->getVertices(),
				                             newFrames);
				
				this->addRenderMode(RenderMode::TEXTURE);
				
				// We load the animations.
				TileMapUtility::readAnimations(polygon.getProperties(),
				                               *this);
				
				// We set the default frame.
				this->setDefaultFrame(TileMapUtility::readDefaultFrame(polygon.getProperties()));
				
				// We start the default animation.
				this->startAnimation(TileMapUtility::readDefaultAnimation(polygon.getProperties()));
				
			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}
			
			
			// We read the rectangle's color.
			this->setColor(TileMapUtility::readColor(polygon.getProperties()));
			
			loadCollidableProperties(polygon.getProperties());
		}
		
		/**
		 * Gets a duplicate of the managed graphic.
		 * @return Pointer to a duplicate of the managed graphic. The caller is
		 * responsible for deleting this instance.
		 */
		virtual GraphicElement<Parent, ManageParent> *clone() const {
			return new GraphicElement<Parent, ManageParent>(*this);
		}
	private:
		/// Makes sure the parent type is at least transformable.
		typedef typename StaticAssert<IsBaseOf<Transformable, Parent>::RESULT || IsSame<Transformable, Parent>::RESULT>::Result IsParentTransformable;
		/// Makes sure the manage parent type is at least manageable.
		typedef typename StaticAssert<IsBaseOf<Manageable, ManageParent>::RESULT || IsSame<Manageable, ManageParent>::RESULT>::Result IsManageParentManageable;
		/**
		 * Loads the properties of a collidable if we are derived from
		 * Collidable.
		 */
		void loadCollidableProperties(const PropertyMap &properties) {
			CallLoadCollidable<GraphicElement<Parent, ManageParent>, IsBaseOf<Collidable, GraphicElement<Parent, ManageParent> >::RESULT>()(properties, *this);
		}
	};
	
	/**
	 * Represents a sprite. A is used to display animated or non-animated
	 * images or display colored shapes. To use a sprite, initialize it and
	 * add it to a State. A sprite can only be in one state at a time. Once
	 * you have given the pointer to the state, you don't have to worry about
	 * deleting it, the state takes care of that for you. To remove a sprite
	 * from a state, simply call setToBeDeleted(true), which is inherited from
	 * Manageable.
	 * @tparam Parent Either Transformable or Collidable.
	 * @ingroup Display
	 * @see RedBox::State
	 */
	template <typename Parent>
	class GraphicElement<Parent, NonManageable> : public Graphic<Animatable>,
	public Parent {
	public:
		/**
		 * Default constructor.
		 */
		GraphicElement() : Graphic<Animatable>(), Parent() {
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
		explicit GraphicElement(TexturePointer newTexture,
		                        const Vector2 &startingPosition = Vector2(),
		                        const Vector2 &newSize = Vector2(),
		                        const Vector2 &newTextureOffset = Vector2(),
		                        unsigned int nbFrames = 1) :
		Graphic<Animatable>(newTexture), Parent(startingPosition) {
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
		 * @param definition Information about the sprite's shape, its frames
		 * and its animations.
		 * @param startingPosition Starting position at which to place the
		 * sprite.
		 */
		GraphicElement(TexturePointer newTexture,
		               const SpriteDefinition &definition,
		               const Vector2 &startingPosition = Vector2()) :
		Graphic<Animatable>(newTexture), Parent(startingPosition) {
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
		 * @param src Managed graphic to make a copy of.
		 */
		GraphicElement(const GraphicElement<Parent, NonManageable> &src) :
		Graphic<Animatable>(src), Parent(src) {
		}
		
		/**
		 * Destructor.
		 */
		virtual ~GraphicElement() {
		}
		
		/**
		 * Assignment operator.
		 * @param src Managed graphic to copy.
		 * @return Reference to the modified managed graphic.
		 */
		GraphicElement<Parent, NonManageable> &operator=(const GraphicElement<Parent, NonManageable> &src) {
			this->Graphic<Animatable>::operator=(src);
			this->Parent::operator=(src);
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
			CallUpdate<GraphicElement<Parent, NonManageable>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);
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
		
		void construct(const Vector2 &newSize,
		               const Vector2 &newPosition,
		               const FrameDetails &frameDetails) {
			
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(newSize, newPosition,
			                              &this->getVertices());
			// We specify the render modes.
			addRenderMode(RenderMode::SHAPE);
			addRenderMode(RenderMode::COLOR);
			
			// We check if we have to initialize the texture coordinates.
			if (getTextureInformation()) {
				loadTextureCoordinates(this->getVertices(), FrameArray(1, frameDetails));
				
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
		
		/**
		 * Constructs the managed graphic from a tile object.
		 * @param tile Tile object to construct the managed graphic from.
		 */
		virtual void construct(const TileObject &tile) {
			this->clearAnimations();
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(tile.getSize(), tile.getPosition() - tile.getHeight(), &this->getVertices());
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);
			
			// We get the texture and the texture coordinates.
			const Tileset *tileset = tile.parentLayer.parentMap.getTileset(tile.getTileId());
			
			if (tileset) {
				this->getFrames().resize(1);
				
				if (tileset->loadTextureCoordinates(tile.getTileId(),
				                                    this->getFrames()[0]) &&
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
		 * Constructs the managed graphic from a rectangle object.
		 * @param rectangle Rectangle object to construct the managed graphic
		 * from.
		 */
		virtual void construct(const RectangleObject &rectangle) {
			this->clearAnimations();
			this->setTextureInformation(TileMapUtility::readTextureKey(rectangle.getProperties()));
			this->Parent::move(rectangle.getXPosition() - this->getXPosition(),
			                   rectangle.getYPosition() - this->getYPosition());
			
			// We initialize the vertices.
			this->getVertices().resize(4);
			ShapeFactory::createRectangle(rectangle.getSize(),
			                              rectangle.getPosition(), &this->getVertices());
			// We specify the render mode.
			this->addRenderMode(RenderMode::SHAPE);
			this->addRenderMode(RenderMode::COLOR);
			
			// We check if we have to initialize the texture coordinates.
			if (this->getTextureInformation()) {
				// We load the texture coordinates.
				FrameArray newFrames;
				TileMapUtility::readFrames(rectangle.getProperties(),
				                           newFrames);
				
				this->loadTextureCoordinates(this->getVertices(),
				                             newFrames);
				
				this->addRenderMode(RenderMode::TEXTURE);
				
				// We load the animations.
				TileMapUtility::readAnimations(rectangle.getProperties(),
				                               *this);
				
				// We set the default frame.
				this->setDefaultFrame(TileMapUtility::readDefaultFrame(rectangle.getProperties()));
				
				// We start the default animation.
				this->startAnimation(TileMapUtility::readDefaultAnimation(rectangle.getProperties()));
				
			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}
			
			
			// We read the rectangle's color.
			this->setColor(TileMapUtility::readColor(rectangle.getProperties()));
			
			loadCollidableProperties(rectangle.getProperties());
		}
		
		/**
		 * Constructs the managed graphic from a polygon object.
		 * @param polygon Polygon object to construct the managed graphic from.
		 */
		virtual void construct(const PolygonObject &polygon) {
			this->clearAnimations();
			this->setTextureInformation(TileMapUtility::readTextureKey(polygon.getProperties()));
			this->Parent::move(polygon.getXPosition() - this->getXPosition(),
			                   polygon.getYPosition() - this->getYPosition());
			
			// We initialize the vertices.
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
				// We load the texture coordinates.
				FrameArray newFrames;
				TileMapUtility::readFrames(polygon.getProperties(),
				                           newFrames);
				
				this->loadTextureCoordinates(this->getVertices(),
				                             newFrames);
				
				this->addRenderMode(RenderMode::TEXTURE);
				
				// We load the animations.
				TileMapUtility::readAnimations(polygon.getProperties(),
				                               *this);
				
				// We set the default frame.
				this->setDefaultFrame(TileMapUtility::readDefaultFrame(polygon.getProperties()));
				
				// We start the default animation.
				this->startAnimation(TileMapUtility::readDefaultAnimation(polygon.getProperties()));
				
			} else {
				this->removeRenderMode(RenderMode::TEXTURE);
			}
			
			
			// We read the rectangle's color.
			this->setColor(TileMapUtility::readColor(polygon.getProperties()));
			
			loadCollidableProperties(polygon.getProperties());
		}
		
		/**
		 * Gets a duplicate of the managed graphic.
		 * @return Pointer to a duplicate of the managed graphic. The caller is
		 * responsible for deleting this instance.
		 */
		virtual GraphicElement<Parent, NonManageable> *clone() const {
			return new GraphicElement<Parent, NonManageable>(*this);
		}
	private:
		/// Makes sure the parent type is at least transformable.
		typedef typename StaticAssert<IsBaseOf<Transformable, Parent>::RESULT || IsSame<Transformable, Parent>::RESULT>::Result IsParentTransformable;
		/**
		 * Loads the properties of a collidable if we are derived from
		 * Collidable.
		 */
		void loadCollidableProperties(const PropertyMap &properties) {
			CallLoadCollidable<GraphicElement<Parent, NonManageable>, IsBaseOf<Collidable, GraphicElement<Parent, NonManageable> >::RESULT>()(properties, *this);
		}
	};
}

#endif

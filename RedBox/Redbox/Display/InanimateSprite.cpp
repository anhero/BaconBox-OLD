#include "InanimateSprite.h"

#include "ShapeFactory.h"
#include "TextureInformation.h"

namespace RedBox {
	InanimateSprite::InanimateSprite() : Graphic<Inanimate>(), Collidable(),
	    Layerable() {
	}

	InanimateSprite::InanimateSprite(const std::string &newTextureKey,
	                                 const Vector2 &startingPosition,
	                                 const Vector2 &newSize,
	                                 const Vector2 &newTextureOffset) :
	    Graphic<Inanimate>(newTextureKey), Collidable(startingPosition), Layerable() {
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

	InanimateSprite::InanimateSprite(const TextureInformation *newTextureInformation,
	                                 const Vector2 &startingPosition,
	                                 const Vector2 &newSize,
	                                 const Vector2 &newTextureOffset) :
	    Graphic<Inanimate>(newTextureInformation), Collidable(startingPosition), Layerable() {
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

	InanimateSprite::InanimateSprite(const InanimateSprite &src) :
		Graphic<Inanimate>(src), Collidable(src), Layerable(src) {
	}

	InanimateSprite::~InanimateSprite() {
	}

	InanimateSprite &InanimateSprite::operator=(const InanimateSprite &src) {
		this->Graphic<Inanimate>::operator=(src);
		this->Collidable::operator=(src);
		this->Layerable::operator=(src);
		return *this;
	}

	void InanimateSprite::move(float xDelta, float yDelta) {
		this->Collidable::move(xDelta, yDelta);
		getVertices().move(xDelta, yDelta);
	}

	const Vector2 InanimateSprite::getCentroid() const {
		return getVertices().getCentroid();
	}

	const Vector2 InanimateSprite::getSize() const {
		return getVertices().getSize();
	}

	float InanimateSprite::getWidth() const {
		return getVertices().getWidth();
	}

	float InanimateSprite::getHeight() const {
		return getVertices().getHeight();
	}

	void InanimateSprite::scaleFromPoint(float xScaling, float yScaling,
	                                     const Vector2 &fromPoint) {
		this->Collidable::scaleFromPoint(xScaling, yScaling, fromPoint);
		getVertices().scaleFromPoint(xScaling, yScaling, fromPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void InanimateSprite::rotateFromPoint(float rotationAngle,
	                                      const Vector2 &rotationPoint) {
		this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
		getVertices().rotateFromPoint(rotationAngle, rotationPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void InanimateSprite::construct(const Vector2 &newSize,
	                                const Vector2 &newPosition,
	                                const Vector2 &newTextureOffset) {
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
}

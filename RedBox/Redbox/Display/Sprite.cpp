#include "Sprite.h"

#include "ShapeFactory.h"
#include "TextureInformation.h"

namespace RedBox {
	Sprite::Sprite() : Graphic<Animatable>(), Collidable(), Layerable() {
	}

	Sprite::Sprite(const std::string &newTextureKey,
	               const Vector2 &startingPosition,
	               const Vector2 &newSize,
	               const Vector2 &newTextureOffset,
	               unsigned int nbFrames) : Graphic<Animatable>(newTextureKey),
		Collidable(startingPosition), Layerable() {
		// We check if we have to use the texture as the full image.
		if (newSize.getX() <= 0.0f || newSize.getY() <= 0.0f) {
			// We make sure the texture information is valid.
			if (this->getTextureInformation()) {
				construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth),
				                  static_cast<float>(this->getTextureInformation()->imageHeight)),
				          startingPosition);
			}
		} else {
			construct(newSize, startingPosition, newTextureOffset, nbFrames);
		}
	}

	Sprite::Sprite(const TextureInformation *newTextureInformation,
	               const Vector2 &startingPosition,
	               const Vector2 &newSize,
	               const Vector2 &newTextureOffset,
	               unsigned int nbFrames) :
	    Graphic<Animatable>(newTextureInformation),
		Collidable(startingPosition), Layerable() {
		// We check if we have to use the texture as the full image.
		if (newSize.getX() <= 0.0f || newSize.getY() <= 0.0f) {
			// We make sure the texture information is valid.
			if (this->getTextureInformation()) {
				construct(Vector2(static_cast<float>(this->getTextureInformation()->imageWidth),
				                  static_cast<float>(this->getTextureInformation()->imageHeight)),
				          startingPosition);
			}
		} else {
			construct(newSize, startingPosition, newTextureOffset, nbFrames);
		}
	}

	Sprite::Sprite(const Sprite &src) : Graphic<Animatable>(src),
	    Collidable(src), Layerable(src) {
	}

	Sprite::~Sprite() {
	}

	Sprite &Sprite::operator=(const Sprite &src) {
		this->Graphic<Animatable>::operator=(src);
		this->Collidable::operator=(src);
		this->Layerable::operator=(src);
		return *this;
	}

	void Sprite::move(float xDelta, float yDelta) {
		this->Collidable::move(xDelta, yDelta);
		this->getVertices().move(xDelta, yDelta);
	}

	const Vector2 Sprite::getCentroid() const {
		return this->getVertices().getCentroid();
	}

	const Vector2 Sprite::getSize() const {
		return this->getVertices().getSize();
	}

	float Sprite::getWidth() const {
		return this->getVertices().getWidth();
	}

	float Sprite::getHeight() const {
		return this->getVertices().getHeight();
	}

	void Sprite::scaleFromPoint(float xScaling, float yScaling,
	                            const Vector2 &fromPoint) {
		this->Collidable::scaleFromPoint(xScaling, yScaling, fromPoint);
		this->getVertices().scaleFromPoint(xScaling, yScaling, fromPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void Sprite::rotateFromPoint(float rotationAngle,
	                             const Vector2 &rotationPoint) {
		this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
		this->getVertices().rotateFromPoint(rotationAngle, rotationPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void Sprite::update() {
		this->Collidable::update();
		this->Graphic<Animatable>::update();
	}

	void Sprite::construct(const Vector2 &newSize, const Vector2 &newPosition,
	                       const Vector2 &newTextureOffset,
	                       unsigned int nbFrames) {
		// We initialize the vertices.
		this->getVertices().resize(4);
		ShapeFactory::createRectangle(newSize, newPosition,
		                              &this->getVertices());
		// We specify the render mode.
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
}

#include "BatchedSprite.h"

#include "ShapeFactory.h"
#include "TextureInformation.h"

namespace RedBox {
	BatchedSprite::BatchedSprite() : BatchedGraphic<Animatable, BatchedSprite>(),
		Collidable(), BatchedBody() {
	}

	BatchedSprite::BatchedSprite(TexturePointer newTexture,
	                             const Vector2 &startingPosition,
	                             const Vector2 &newSize,
	                             const Vector2 &newTextureOffset,
	                             unsigned int nbFrames) :
		BatchedGraphic<Animatable, BatchedSprite>(newTexture),
		Collidable(startingPosition), BatchedBody() {
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

	BatchedSprite::~BatchedSprite() {
	}

	void BatchedSprite::move(float xDelta, float yDelta) {
		this->Collidable::move(xDelta, yDelta);
		this->getVertices().move(xDelta, yDelta);
	}

	const Vector2 BatchedSprite::getCentroid() const {
		return this->getVertices().getCentroid();
	}

	const Vector2 BatchedSprite::getSize() const {
		return this->getVertices().getSize();
	}

	float BatchedSprite::getWidth() const {
		return this->getVertices().getWidth();
	}

	float BatchedSprite::getHeight() const {
		return this->getVertices().getHeight();
	}

	void BatchedSprite::scaleFromPoint(float xScaling, float yScaling,
	                                   const Vector2 &fromPoint) {
		this->Collidable::scaleFromPoint(xScaling, yScaling, fromPoint);
		this->getVertices().scaleFromPoint(xScaling, yScaling, fromPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void BatchedSprite::rotateFromPoint(float rotationAngle,
	                                    const Vector2 &rotationPoint) {
		this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
		this->getVertices().rotateFromPoint(rotationAngle, rotationPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void BatchedSprite::update() {
		this->Collidable::update();
		this->BatchedGraphic<Animatable, BatchedSprite>::update();
	}

	void BatchedSprite::construct(const Vector2 &newSize, const Vector2 &newPosition,
	                              const Vector2 &newTextureOffset,
	                              unsigned int nbFrames) {
		// We initialize the vertices.
		this->getVertices().resize(4);
		ShapeFactory::createRectangle(newSize, newPosition,
		                              &this->getVertices());

		// We check if we have to initialize the texture coordinates.
		if (getTextureInformation()) {
			loadTextureCoordinates(this->getVertices(), newTextureOffset,
			                       nbFrames);
		}

		this->refreshTextureCoordinates();
	}

	BatchedSprite::BatchedSprite(RenderBatch<BatchedSprite> *newBatch,
	                             VertexArray::ContainerType *newVertices) :
		BatchedGraphic<Animatable, BatchedSprite>(),
		Collidable(), BatchedBody() {
	}

	BatchedSprite::BatchedSprite(RenderBatch<BatchedSprite> *newBatch,
	                             VertexArray::SizeType newBegin,
	                             VertexArray::SizeType newNbVertices) {
	}
}

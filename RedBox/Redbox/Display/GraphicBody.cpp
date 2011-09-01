#include "GraphicBody.h"
#include "Engine.h"

#include <cfloat>
#include <cmath>

#include <algorithm>

#include "Random.h"

#define RB_OVERLAP_BIAS 4.0f

using namespace RedBox;

FlagSet<Side> initAllSides();

const FlagSet<Side> GraphicBody::ALL_SIDES = initAllSides();

FlagSet<Side> initAllSides() {
	FlagSet<Side> result;
	result.set(Side::LEFT);
	result.set(Side::RIGHT);
	result.set(Side::TOP);
	result.set(Side::BOTTOM);
	return result;
}

GraphicBody::GraphicBody(const Vector2& newPosition) : Body(),
	position(newPosition), maxVelocity(Vector2(NO_MAX_VELOCITY, NO_MAX_VELOCITY)),
	scaling(Vector2(1.0f, 1.0f)), angle(0.0f), collidableSides(ALL_SIDES),
	elasticity(0.0f), staticBody(false), toBeDeleted(false),
	layerChanged(false), isInState(false), collidingBoxRatio(1.0f, 1.0f) {
}

GraphicBody::GraphicBody(const GraphicBody& src) : Body(src) {
	copyFrom(src);
}

GraphicBody::~GraphicBody() {
}

GraphicBody& GraphicBody::operator=(const GraphicBody& src) {
	Body::operator=(src);
	copyFrom(src);
	return *this;
}

void GraphicBody::update() {
	float ratio = Engine::getSinceLastUpdate();
	oldPosition = position;

	// Update horizontal motion.
	float velocityDelta = (computeVelocity(velocity.getX(), acceleration.getX(), drag.getX(), maxVelocity.getX()) - velocity.getX()) * 0.5f;
	velocity.addToX(velocityDelta);
	float delta = velocity.getX() * ratio;
	velocity.addToX(velocityDelta);
	position.addToX(delta);

	// Update vertical motion.
	velocityDelta = (computeVelocity(velocity.getY(), acceleration.getY(), drag.getY(), maxVelocity.getY()) - velocity.getY()) * 0.5f;
	velocity.addToY(velocityDelta);
	delta = velocity.getY() * ratio;
	velocity.addToY(velocityDelta);
	position.addToY(delta);

	if(oldPosition != position) {
		this->setPosition(position.getX(), position.getY());
	}
}

const Layer& GraphicBody::getLayer() const {
	return layer;
}

void GraphicBody::setLayer(const Layer& newLayer) {
	layer = newLayer;
	layerChanged = true;
}

int GraphicBody::getZ() const {
	return layer.getZ();
}

void GraphicBody::setZ(int newZ) {
	layer.setZ(newZ);
	layerChanged = true;
}

const Vector2& GraphicBody::getScrollFactor() const {
	return layer.getScrollFactor();
}

void GraphicBody::setScrollFactor(const Vector2& newScrollFactor) {
	layer.setScrollFactor(newScrollFactor);
	layerChanged = true;
}

void GraphicBody::setScrollFactor(float newXScrollFactor,
                                  float newYScrollFactor) {
	layer.setScrollFactor(newXScrollFactor, newYScrollFactor);
	layerChanged = true;
}

float GraphicBody::getXScrollFactor() const {
	return layer.getXScrollFactor();
}

void GraphicBody::setXScrollFactor(float newXScrollFactor) {
	layer.setXScrollFactor(newXScrollFactor);
	layerChanged = true;
}

float GraphicBody::getYScrollFactor() const {
	return layer.getYScrollFactor();
}

void GraphicBody::setYScrollFactor(float newYScrollFactor) {
	layer.setYScrollFactor(newYScrollFactor);
	layerChanged = true;
}

bool GraphicBody::isToBeDeleted() const {
	return toBeDeleted;
}

void GraphicBody::setToBeDeleted(bool newToBeDeleted) {
	toBeDeleted = newToBeDeleted;
}

bool GraphicBody::isLayerChanged() const {
	return layerChanged;
}

const Vector2& GraphicBody::getVelocity() const {
	return velocity;
}

void GraphicBody::setVelocity(const Vector2& newVelocity) {
	velocity = newVelocity;
}

void GraphicBody::setVelocity(float newXVelocity, float newYVelocity) {
	velocity.setXY(newXVelocity, newYVelocity);
}

float GraphicBody::getXVelocity() const {
	return velocity.getX();
}

void GraphicBody::setXVelocity(float newXVelocity) {
	velocity.setX(newXVelocity);
}

float GraphicBody::getYVelocity() const {
	return velocity.getY();
}

void GraphicBody::setYVelocity(float newYVelocity) {
	velocity.setY(newYVelocity);
}

const Vector2& GraphicBody::getAcceleration() const {
	return acceleration;
}

void GraphicBody::setAcceleration(const Vector2& newAcceleration) {
	acceleration = newAcceleration;
}

void GraphicBody::setAcceleration(float newXAcceleration,
                                  float newYAcceleration) {
	acceleration.setXY(newXAcceleration, newYAcceleration);
}

float GraphicBody::getXAcceleration() const {
	return acceleration.getX();
}

void GraphicBody::setXAcceleration(float newXAcceleration) {
	acceleration.setX(newXAcceleration);
}

float GraphicBody::getYAcceleration() const {
	return acceleration.getY();
}

void GraphicBody::setYAcceleration(float newYAccelaration) {
	acceleration.setY(newYAccelaration);
}

const Vector2& GraphicBody::getPosition() const {
	return position;
}

void GraphicBody::setPosition(const Vector2& newPosition) {
	setPosition(newPosition.getX(), newPosition.getY());
}

void GraphicBody::setPosition(float newXPosition, float newYPosition) {
	position.setXY(newXPosition, newYPosition);
}

void GraphicBody::move(const Vector2& delta) {
	setPosition(position + delta);
}

void GraphicBody::move(float deltaX, float deltaY) {
	setPosition(position + Vector2(deltaX, deltaY));
}

float GraphicBody::getXPosition() const {
	return position.getX();
}

void GraphicBody::setXPosition(float newXPosition) {
	setPosition(newXPosition, getYPosition());
}

void GraphicBody::moveX(float deltaX) {
	setXPosition(position.getX() + deltaX);
}

float GraphicBody::getYPosition() const {
	return position.getY();
}

void GraphicBody::setYPosition(float newYPosition) {
	setPosition(getXPosition(), newYPosition);
}

void GraphicBody::moveY(float deltaY) {
	setYPosition(position.getY() + deltaY);
}

const Vector2& GraphicBody::getOldPosition() const {
	return oldPosition;
}

float GraphicBody::getOldXPosition() const {
	return oldPosition.getX();
}

float GraphicBody::getOldYPosition() const {
	return oldPosition.getY();
}

const Vector2 GraphicBody::getPositionCenter() const {
	return Vector2(getXPositionCenter(), getYPositionCenter());
}

float GraphicBody::getXPositionCenter() const {
	return getXPosition() + getWidth() * 0.5f;
}

float GraphicBody::getYPositionCenter() const {
	return getYPosition() + getHeight() * 0.5f;
}

const Vector2& GraphicBody::getMaxVelocity() const {
	return maxVelocity;
}

void GraphicBody::setMaxVelocity(const Vector2& newMaxVelocity) {
	maxVelocity = newMaxVelocity;
}

void GraphicBody::setMaxVelocity(float newMaxXVelocity, float newMaxYVelocity) {
	maxVelocity.setXY(newMaxXVelocity, newMaxYVelocity);
}

float GraphicBody::getMaxXVelocity() const {
	return maxVelocity.getX();
}

void GraphicBody::setMaxXVelocity(float newMaxXVelocity) {
	maxVelocity.setX(newMaxXVelocity);
}

float GraphicBody::getMaxYVelocity() const {
	return maxVelocity.getY();
}

void GraphicBody::setMaxYVelocity(float newMaxYVelocity) {
	maxVelocity.setY(newMaxYVelocity);
}

const Vector2 GraphicBody::getSize() const {
	return Vector2(getWidth(), getHeight());
}

FlagSet<Side>& GraphicBody::getCollidableSides() {
	return collidableSides;
}

bool GraphicBody::isStaticBody() const {
	return staticBody;
}

void GraphicBody::setStaticBody(bool newStaticBody) {
	staticBody = newStaticBody;
}

float GraphicBody::getElasticity() const {
	return elasticity;
}

void GraphicBody::setElasticity(float newElasticity) {
	elasticity = newElasticity;
}

std::pair<bool, CollisionData> GraphicBody::collide(GraphicBody* other) {
	return collide(this, other);
}

std::pair<bool, std::list<CollisionData> > GraphicBody::collide(const std::list<GraphicBody*>& graphicBodies) {
	std::list<CollisionData> collisionInfo;
	bool collide = false;

	std::pair<bool, CollisionData> collisionPair;
	for(std::list<GraphicBody*>::const_iterator i = graphicBodies.begin();
		i != graphicBodies.end(); ++i) {

		collisionPair = this->collide(*i);

		if(collisionPair.first) {
			collide = true;
		}

		collisionInfo.push_back(collisionPair.second);
	}

	return std::pair<bool, std::list<CollisionData> >(collide,  collisionInfo);
}

bool GraphicBody::horizLineCollide(float linePosition, float lowerXBoundary, float higherXBoundary) {
	return horizLineCollide(this, linePosition, lowerXBoundary, higherXBoundary);
}

bool GraphicBody::vertLineCollide(float linePosition, float lowerYBoundary, float higherYBoundary) {
	return vertLineCollide(this, linePosition, lowerYBoundary, higherYBoundary);
}

float GraphicBody::computeVelocity(float velocity, float acceleration, float drag, float max) {
	if(acceleration) {
		velocity += acceleration * Engine::getSinceLastUpdate();
	} else if(drag) {
		float tmpDrag = drag * Engine::getSinceLastUpdate();

		if(velocity - tmpDrag > 0.0f) {
			velocity -= tmpDrag;
		} else if(velocity + tmpDrag < 0.0f) {
			velocity += tmpDrag;
		} else {
			velocity = 0.0f;
		}
	}

	if(velocity && max != NO_MAX_VELOCITY) {
		if(velocity > max) {
			velocity = max;
		} else if(velocity < -max) {
			velocity = -max;
		}
	}

	return velocity;
}

AABB GraphicBody::getAABB() const {
	return AABB(getXPosition() + getXOffset(), getXPosition() + getXOffset() + getWidth() * getXCollidingBoxRatio(), getYPosition() + getYOffset(), getYPosition() + getYOffset() + getHeight() * getYCollidingBoxRatio());
}

const Vector2& GraphicBody::getDrag() const {
	return drag;
}

void GraphicBody::setDrag(const Vector2& newDrag) {
	drag = newDrag;
}

void GraphicBody::setDrag(float newXDrag, float newYDrag) {
	drag.setXY(newXDrag, newYDrag);
}

float GraphicBody::getXDrag() const {
	return drag.getX();
}

void GraphicBody::setXDrag(float newXDrag) {
	drag.setX(newXDrag);
}

float GraphicBody::getYDrag() const {
	return drag.getY();
}

void GraphicBody::setYDrag(float newYDrag) {
	drag.setY(newYDrag);
}

const Vector2& GraphicBody::getScaling() const {
	return scaling;
}

void GraphicBody::setScaling(const Vector2& newScaling) {
	setScaling(newScaling.getX(), newScaling.getY());
}

void GraphicBody::setScaling(float newXScaling, float newYScaling) {
	scaling.setXY(newXScaling, newYScaling);
}

void GraphicBody::addToScaling(const Vector2& scalingToAdd) {
	addToScaling(scalingToAdd.getX(), scalingToAdd.getY());
}

void GraphicBody::addToScaling(float xScaling, float yScaling) {
	if(xScaling || yScaling) {
		if(xScaling + scaling.getX() == 0.0f) {
			if(xScaling > 0.0f) {
				xScaling += FLT_MIN;
			} else if(xScaling < 0.0f) {
				xScaling -= FLT_MIN;
			}
		}

		if(yScaling + scaling.getY() == 0.0f) {
			if(yScaling > 0.0f) {
				yScaling += FLT_MIN;
			} else if(yScaling < 0.0f) {
				yScaling -= FLT_MIN;
			}
		}

		setScaling(scaling.getX() + xScaling, scaling.getY() + yScaling);
	}
}

float GraphicBody::getXScaling() const {
	return scaling.getX();
}

void GraphicBody::setXScaling(float newXScaling) {
	setScaling(newXScaling, scaling.getY());
}

float GraphicBody::getYScaling() const {
	return scaling.getY();
}

void GraphicBody::setYScaling(float newYScaling) {
	setScaling(scaling.getX(), newYScaling);
}

float GraphicBody::getAngle() const {
	return angle;
}

void GraphicBody::setAngle(float newAngle) {
	rotate(newAngle - angle);
}

void GraphicBody::rotate(float angleToAdd) {
	rotateFromPoint(angleToAdd, getPosition() + Vector2(getWidth(), getHeight()) * 0.5f);
}

void GraphicBody::rotateFromPoint(float rotationAngle, const Vector2&) {
	angle = fmodf(angle += rotationAngle, 360.0f);
}

const Vector2& GraphicBody::getOffset() const {
	return offset;
}

void GraphicBody::setOffset(const Vector2& newOffset) {
	offset = newOffset;
}

void GraphicBody::setOffset(float newXOffset, float newYOffset) {
	offset.setXY(newXOffset, newYOffset);
}

float GraphicBody::getXOffset() const {
	return offset.getX();
}

void GraphicBody::setXOffset(float newXOffset) {
	offset.setX(newXOffset);
}

float GraphicBody::getYOffset() const {
	return offset.getX();
}

void GraphicBody::setYOffset(float newYOffset) {
	offset.setY(newYOffset);
}

const Vector2& GraphicBody::getCollidingBoxRatio() const {
	return collidingBoxRatio;
}

void GraphicBody::setCollidingBoxRatio(const Vector2& newCollidingBoxRatio) {
	collidingBoxRatio = newCollidingBoxRatio;
}

void GraphicBody::setCollidingBoxRatio(float newXCollidingBoxRatio,
									   float newYCollidingBoxRatio) {
	collidingBoxRatio.setXY(newXCollidingBoxRatio, newYCollidingBoxRatio);
}

float GraphicBody::getXCollidingBoxRatio() const {
	return collidingBoxRatio.getX();
}

void GraphicBody::setXCollidingBoxRatio(float newXCollidingBoxRatio) {
	collidingBoxRatio.setX(newXCollidingBoxRatio);
}

float GraphicBody::getYCollidingBoxRatio() const {
	return collidingBoxRatio.getY();
}

void GraphicBody::setYCollidingBoxRatio(float newYCollidingBoxRatio) {
	collidingBoxRatio.setY(newYCollidingBoxRatio);
}

std::pair<bool, CollisionData> GraphicBody::collide(GraphicBody* body1,
        GraphicBody* body2) {
	CollisionData currentCollisionData;
	currentCollisionData.obj1 = body1;
	currentCollisionData.obj2 = body2;

	if(body1 != body2) {
		bool collideInX = solveXCollision(body1, body2, &currentCollisionData);
		bool collideInY = solveYCollision(body1, body2, &currentCollisionData);
		return std::pair<bool, CollisionData>(collideInX || collideInY,
		                                      currentCollisionData);
	} else {
		return std::pair<bool, CollisionData>(false, currentCollisionData);
	}
}

std::pair<bool, std::list<CollisionData> > GraphicBody::collide(std::list<GraphicBody*> graphicBodies1,
        std::list<GraphicBody*> graphicBodies2) {
	std::list<CollisionData> collisionInfo;
	bool collide = false;

	for(std::list<GraphicBody*>::iterator i = graphicBodies1.begin();
	        i != graphicBodies1.end(); ++i) {

		for(std::list<GraphicBody*>::iterator j = graphicBodies2.begin();
		        j != graphicBodies2.end(); ++j) {

			if(*i != *j) {
				std::pair<bool, CollisionData> collisionPair = GraphicBody::collide(*i, *j);

				if(collisionPair.first) {
					collide = true;
				}

				collisionInfo.push_back(collisionPair.second);
			}
		}
	}

	return std::pair<bool, std::list<CollisionData> >(collide,  collisionInfo);
}

bool GraphicBody::horizLineCollide(GraphicBody* aGraphicBody, float linePosition, float lowerXBoundary, float higherXBoundary) {
	bool result = false;

	//linePosition -= aGraphicBody->getYOffset();
	//lowerXBoundary -= aGraphicBody->getXOffset();
	//higherXBoundary -= aGraphicBody->getXOffset();

	// We make sure the given graphic body is valid.
	if(aGraphicBody && !aGraphicBody->isStaticBody()) {
		float delta = aGraphicBody->getYPosition() - aGraphicBody->getOldYPosition();
		float tmpHeight = aGraphicBody->getHeight() * aGraphicBody->getYCollidingBoxRatio();

		// We check if the body overlaps with the horizontal line.
		if(aGraphicBody->getAABB().horizLineOverlaps(linePosition, lowerXBoundary, higherXBoundary)) {
			// If the body is going down.
			if(delta > 0.0f) {
				// We put the body's bottom at the line's position.
				aGraphicBody->setYPosition(linePosition - tmpHeight);
				// If the body is going up.
			} else if(delta < 0.0f) {
				// We put the body's top at the line's position.
				aGraphicBody->setYPosition(linePosition);
			} else if(aGraphicBody->getYPosition() + tmpHeight * 0.5f < linePosition) {
				aGraphicBody->setYPosition(linePosition - tmpHeight);
			} else {
				aGraphicBody->setYPosition(linePosition);
			}

			aGraphicBody->setYVelocity(-aGraphicBody->getYVelocity() * aGraphicBody->getElasticity());

			result = true;
		}

	}

	return result;
}

bool GraphicBody::vertLineCollide(GraphicBody* aGraphicBody, float linePosition,
                                  float lowerYBoundary, float higherYBoundary) {
	bool result = false;

	//linePosition -= aGraphicBody->getXOffset();
	//lowerYBoundary -= aGraphicBody->getYOffset();
	//higherYBoundary -= aGraphicBody->getYOffset();

	// We make sure the given graphic body is valid.
	if(aGraphicBody && !aGraphicBody->isStaticBody()) {
		float delta = aGraphicBody->getXPosition() - aGraphicBody->getOldXPosition();
		float tmpWidth = aGraphicBody->getWidth() * aGraphicBody->getXCollidingBoxRatio();

		// We check if the body overlaps with the horizontal line.
		if(aGraphicBody->getAABB().vertLineOverlaps(linePosition, lowerYBoundary, higherYBoundary)) {
			// If the body is going down.
			if(delta > 0.0f) {
				// We put the body's bottom at the line's position.
				aGraphicBody->setXPosition(linePosition - tmpWidth);
				// If the body is going up.
			} else if(delta < 0.0f) {
				// We put the body's top at the line's position.
				aGraphicBody->setXPosition(linePosition);
			} else if(aGraphicBody->getXPosition() + tmpWidth * 0.5f < linePosition) {
				aGraphicBody->setXPosition(linePosition - tmpWidth);
			} else {
				aGraphicBody->setXPosition(linePosition);
			}

			aGraphicBody->setXVelocity(-aGraphicBody->getXVelocity() * aGraphicBody->getElasticity());

			result = true;
		}

	}

	return result;
}

bool GraphicBody::solveXCollision(GraphicBody* object1, GraphicBody* object2, CollisionData* collisionInfo) {
	// We check if both instance are static
	if(object1->isStaticBody() && object2->isStaticBody()) {
		return false;
	}

	// We calculate object delta
	float overlap = 0.0f,
			obj1Delta = object1->getXPosition() - object1->getOldXPosition(),
			obj2Delta = object2->getXPosition() - object2->getOldXPosition();

	if(obj1Delta != obj2Delta) {
		// We calculate absolute delta
		float obj1DeltaAbs = fabs(obj1Delta), obj2DeltaAbs = fabs(obj2Delta),
				tmpWidth1 = 0.0f, tmpWidth2 = 0.0f;

		// We create AABBs of the old position with the updated horizontal
		//position.

		tmpWidth1 = object1->getWidth() * object1->getXCollidingBoxRatio();
		tmpWidth2 = object2->getWidth() * object2->getXCollidingBoxRatio();

		AABB obj1AABB(object1->getXPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)) + object1->getXOffset(),
					  object1->getXPosition() + tmpWidth1 + obj1DeltaAbs + object1->getXOffset(),
					  object1->getOldYPosition() + object1->getYOffset(),
					  object1->getOldYPosition() + object1->getHeight() * object1->getYCollidingBoxRatio() + object1->getYOffset());

		AABB obj2AABB(object2->getXPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)) + object2->getXOffset(),
					  object2->getXPosition() + tmpWidth2 + obj2DeltaAbs + object2->getXOffset(),
					  object2->getOldYPosition() + object2->getYOffset(),
					  object2->getOldYPosition() + object2->getHeight() * object2->getYCollidingBoxRatio() + object2->getYOffset());

		if(obj1AABB.overlaps(obj2AABB)) {

			float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + RB_OVERLAP_BIAS;

			if(obj1Delta > obj2Delta) {
				overlap = (object1->getXPosition() + object1->getXOffset()) + tmpWidth1 - (object2->getXPosition() + object2->getXOffset());

				if(overlap > maxOverlap || !object1->collidableSides.isSet(Side::RIGHT) || !object2->collidableSides.isSet(Side::LEFT)) {
					overlap = 0.0f;
				} else {
					collisionInfo->sideObj1 = Side::RIGHT;
					collisionInfo->sideObj2 = Side::LEFT;
				}

			} else if(obj1Delta < obj2Delta) {
				overlap = object1->getXPosition() - tmpWidth2 - object2->getXPosition();

				if((-overlap > maxOverlap) || !object1->collidableSides.isSet(Side::LEFT) || !object2->collidableSides.isSet(Side::RIGHT)) {
					overlap = 0.0f;
				} else {
					collisionInfo->sideObj1 = Side::LEFT;
					collisionInfo->sideObj2 = Side::RIGHT;
				}
			}
		}
	}

	if(overlap) {
		float obj1v = object1->getXVelocity();
		float obj2v = object2->getXVelocity();

		if(!object1->isStaticBody() && !object2->isStaticBody()) {
			overlap *= 0.5f;

			object1->moveX(-overlap);
			object2->moveX(overlap);

			float average = (obj2v + obj2v) * 0.5f;

			object1->setXVelocity(average + (obj2v - average) * object1->getElasticity());
			object2->setXVelocity(average + (obj1v - average) * object2->getElasticity());
		} else if(!object1->isStaticBody()) {
			object1->moveX(-overlap);
			object1->setXVelocity(obj2v - (obj1v * object1->getElasticity()));

		} else if(!object2->isStaticBody()) {
			object2->moveX(overlap);

			object2->setXVelocity(obj1v - (obj2v * object2->getElasticity()));
		}

		return true;

	} else {
		return false;
	}
}

bool GraphicBody::solveYCollision(GraphicBody* object1, GraphicBody* object2, CollisionData* collisionInfo) {
	//We check if both instance are static
	if(object1->isStaticBody() && object2->isStaticBody()) {
		return false;
	}

	//We calculate object delta
	float overlap = 0.0f,
			obj1Delta = object1->getYPosition() - object1->getOldYPosition(),
			obj2Delta = object2->getYPosition() - object2->getOldYPosition();

	if(obj1Delta != obj2Delta) {
		//We calculate absolute delta
		float obj1DeltaAbs = fabs(obj1Delta), obj2DeltaAbs = fabs(obj2Delta),
				tmpHeight1 = 0.0f, tmpHeight2 = 0.0f;

		tmpHeight1 = object1->getHeight() * object1->getYCollidingBoxRatio();
		tmpHeight2 = object2->getHeight() * object2->getYCollidingBoxRatio();
		// We create AABBs of the old position with the updated vertical
		// position.
		AABB obj1AABB(object1->getXPosition() + object1->getXOffset(),
					  object1->getXPosition() + object1->getWidth() * object1->getXCollidingBoxRatio() + object1->getXOffset(),
					  object1->getYPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)) + object1->getYOffset(),
					  object1->getYPosition() + tmpHeight1 + obj1DeltaAbs + object1->getYOffset());

		AABB obj2AABB(object2->getXPosition() + object2->getXOffset(),
					  object2->getXPosition() + object2->getWidth() * object2->getXCollidingBoxRatio() + object2->getXOffset(),
					  object2->getYPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)) + object2->getYOffset(),
					  object2->getYPosition() + tmpHeight2 + obj2DeltaAbs + object2->getYOffset());


		// We check if the objects are colliding.
		if(obj1AABB.overlaps(obj2AABB)) {
			// We calculate the maximum overlap.
			float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + RB_OVERLAP_BIAS;

			// If the first object is moving to the bottom faster than the
			// second body.
			if(obj1Delta > obj2Delta) {
				overlap = (object1->getYPosition() + object1->getYOffset()) + tmpHeight1 - (object2->getYPosition() + object2->getYOffset());

				if(overlap > maxOverlap || !object1->collidableSides.isSet(Side::BOTTOM) || !object2->collidableSides.isSet(Side::TOP)) {
					overlap = 0.0f;
				} else {
					collisionInfo->sideObj1 = Side::BOTTOM;
					collisionInfo->sideObj2 = Side::TOP;
				}

			} else if(obj1Delta < obj2Delta) {
				overlap = object1->getYPosition() - tmpHeight2 - object2->getYPosition();

				if(-overlap > maxOverlap || !object1->collidableSides.isSet(Side::TOP) || !object2->collidableSides.isSet(Side::BOTTOM)) {
					overlap = 0.0f;
				} else {
					collisionInfo->sideObj1 = Side::TOP;
					collisionInfo->sideObj2 = Side::BOTTOM;
				}
			}

		}
	}

	if(overlap) {
		float obj1v = object1->getVelocity().getY();
		float obj2v = object2->getVelocity().getY();

		if(!object1->isStaticBody() && !object2->isStaticBody()) {
			overlap *= 0.5f;
			object1->moveY(-overlap);
			object2->moveY(overlap);

			float average = (obj1v + obj2v) * 0.5;

			object1->setYVelocity(average + (obj2v - average) * object1->getElasticity());
			object2->setYVelocity(average + (obj1v - average) * object2->getElasticity());

		} else if(!object1->isStaticBody()) {
			object1->moveY(-overlap);

			object1->setYVelocity(obj2v - obj1v * object1->getElasticity());

			//Handle horizontal moving static object EX. moving platform
			if(obj1Delta > obj2Delta) {
				object1->setXPosition(object1->getXPosition() + (object2->getXPosition() - object2->getOldXPosition()));
			}

		} else if(!object2->isStaticBody()) {
			object2->moveY(overlap);

			object2->setYVelocity(obj1v - obj2v * object2->getElasticity());

			// Handle horizontal moving static object EX. moving platform
			if(obj1Delta < obj2Delta) {
				object2->setXPosition(object2->getXPosition() + object1->getXPosition() - object1->getOldXPosition());
			}
		}

		return true;
	} else {
		return false;
	}
}

void GraphicBody::resetLayerChanged() {
	layerChanged = false;
}

void GraphicBody::copyFrom(const GraphicBody& src) {
	if(this != &src && &src) {
		position = src.position;
		oldPosition = position;
		velocity = Vector2();
		acceleration = src.acceleration;
		drag = src.drag;
		maxVelocity = src.maxVelocity;
		scaling = src.scaling;
		angle = src.angle;
		staticBody = src.staticBody;
		layer = src.layer;
		toBeDeleted = false;
		layerChanged = true;
		isInState = false;
		offset = src.offset;
		collidingBoxRatio = src.collidingBoxRatio;
	}
}

#include "GraphicBody.h"
#include "Engine.h"

#include <cfloat>
#include <cmath>

#define RB_OVERLAP_BIAS 4

using namespace RedBox;

GraphicBody::GraphicBody() : Object(),
	maxVelocity(Vec2(NO_MAX_VELOCITY, NO_MAX_VELOCITY)),
	scaling(Vec2(1.0f, 1.0f)), angle(0.0f), layer(Layer()), toBeDeleted(false),
	layerChanged(false), isInState(false), collidableSides(Side::ALL),
	elasticity(0.0f), staticObject(false), drag(Vec2(0.0f, 0.0f)) {
}

GraphicBody::GraphicBody(const GraphicBody& src) : Object(src) {
	copyFrom(src);
}

GraphicBody::~GraphicBody() {
}

GraphicBody& GraphicBody::operator=(const GraphicBody& src) {
	Object::operator=(src);
	copyFrom(src);
	return *this;
}

void GraphicBody::update() {
	float ratio = Engine::getSinceLastUpdate();
	oldPosition = position;


	if(maxVelocity.getX() != NO_MAX_VELOCITY) {

		if(velocity.getX() < -maxVelocity.getX()) {
			velocity.setX(-maxVelocity.getX());
		} else if(velocity.getX() > maxVelocity.getX()) {
			velocity.setX(maxVelocity.getX());
		}
	}

	if(maxVelocity.getY() != NO_MAX_VELOCITY) {

		if(velocity.getY() < -maxVelocity.getY()) {
			velocity.setY(-maxVelocity.getY());
		} else if(velocity.getY() > maxVelocity.getY()) {
			velocity.setY(maxVelocity.getY());
		}
	}

	if(acceleration.getX() == 0.0f) {
		if(velocity.getX() > 0.0f) {
			velocity.setX(velocity.getX() - drag.getX() * ratio);

			if(velocity.getX() < 0.0f) {
				velocity.setX(0.0f);
			}
		} else if(velocity.getX() < 0.0f) {
			velocity.setX(velocity.getX() + drag.getX() * ratio);

			if(velocity.getX() > 0.0f) {
				velocity.setX(0.0f);
			}
		}
	}

	if(acceleration.getY() == 0.0f) {
		if(velocity.getY() > 0.0f) {
			velocity.setY(velocity.getY() - drag.getY() * ratio);

			if(velocity.getY() < 0.0f) {
				velocity.setY(0.0f);
			}
		} else if(velocity.getY() < 0.0f) {
			velocity.setY(velocity.getY() + drag.getY() * ratio);

			if(velocity.getY() > 0.0f) {
				velocity.setY(0.0f);
			}
		}
	}

	velocity += (acceleration * ratio);
	position += (velocity * ratio);
	this->setPosition(position.getX(), position.getY());
}

const Layer& GraphicBody::getLayer() const {
	return layer;
}

void GraphicBody::setLayer(const Layer& newLayer) {
	layer = newLayer;
	layerChanged = true;
}

void GraphicBody::setZ(int newZ) {
	layer.setZ(newZ);
}

void GraphicBody::setScrollFactor(const Vec2& newScrollFactor) {
	layer.setScrollFactor(newScrollFactor);
}

void GraphicBody::setXScrollFactor(float newXScrollFactor) {
	layer.setXScrollFactor(newXScrollFactor);
}

void GraphicBody::setYScrollFactor(float newYScrollFactor) {
	layer.setYScrollFactor(newYScrollFactor);
}

int GraphicBody::getZ() const {
	return layer.getZ();
}

const Vec2& GraphicBody::getScrollFactor() const {
	return layer.getScrollFactor();
}

float GraphicBody::getXScrollFactor() const {
	return layer.getXScrollFactor();
}

float GraphicBody::getYScrollFactor() const {
	return layer.getYScrollFactor();
}

bool GraphicBody::isToBeDeleted() const {
	return toBeDeleted;
}

bool GraphicBody::isLayerChanged() const {
	return layerChanged;
}

void GraphicBody::setToBeDeleted(bool newToBeDeleted) {
	toBeDeleted = newToBeDeleted;
}

void GraphicBody::resetLayerChanged() {
	layerChanged = false;
}

void GraphicBody::setVelocity(const Vec2& newVelocity) {
	velocity = newVelocity;
}

void GraphicBody::setVelocity(float newXVelocity, float newYVelocity) {
	velocity.setXY(newXVelocity, newYVelocity);
}

void GraphicBody::setXVelocity(float newXVelocity) {
	velocity.setX(newXVelocity);
}

void GraphicBody::setYVelocity(float newYVelocity) {
	velocity.setY(newYVelocity);
}

const Vec2& GraphicBody::getVelocity() const {
	return velocity;
}

float GraphicBody::getXVelocity() const {
	return velocity.getX();
}

float GraphicBody::getYVelocity() const {
	return velocity.getY();
}

void GraphicBody::setAcceleration(const Vec2& newAcceleration) {
	acceleration = newAcceleration;
}

void GraphicBody::setAcceleration(float newXAcceleration,
                                  float newYAcceleration) {
	acceleration.setXY(newXAcceleration, newYAcceleration);
}

void GraphicBody::setXAcceleration(float newXAcceleration) {
	acceleration.setX(newXAcceleration);
}

void GraphicBody::setYAcceleration(float newYAccelaration) {
	acceleration.setY(newYAccelaration);
}

const Vec2& GraphicBody::getAcceleration() const {
	return acceleration;
}

float GraphicBody::getXAcceleration() const {
	return acceleration.getX();
}

float GraphicBody::getYAcceleration() const {
	return acceleration.getY();
}

const Vec2& GraphicBody::getPosition() const {
	return position;
}

float GraphicBody::getXPosition() const {
	return position.getX();
}

float GraphicBody::getYPosition() const {
	return position.getY();
}

void GraphicBody::setPosition(const Vec2& newPosition) {
	setPosition(newPosition.getX(), newPosition.getY());
}

void GraphicBody::setPosition(float x, float y) {
	position.setXY(x, y);
}

void GraphicBody::setXPosition(float x) {
	position.setX(x);
}

void GraphicBody::setYPosition(float y) {
	position.setY(y);
}

const Vec2& GraphicBody::getOldPosition() const {
	return oldPosition;
}

float GraphicBody::getOldXPosition() const {
	return oldPosition.getX();
}

float GraphicBody::getOldYPosition() const {
	return oldPosition.getY();
}

void GraphicBody::move(const Vec2& delta) {
	setPosition(position + delta);
}

void GraphicBody::move(float deltaX, float deltaY) {
	setPosition(position + Vec2(deltaX, deltaY));
}

void GraphicBody::moveX(float deltaX) {
	setXPosition(position.getX() + deltaX);
}

void GraphicBody::moveY(float deltaY) {
	setYPosition(position.getY() + deltaY);
}

void GraphicBody::setMaxVelocity(const Vec2& newMaxVelocity) {
	maxVelocity = newMaxVelocity;
}

void GraphicBody::setMaxVelocity(float newMaxXVelocity, float newMaxYVelocity) {
	maxVelocity.setXY(newMaxXVelocity, newMaxYVelocity);
}

void GraphicBody::setMaxXVelocity(float newMaxXVelocity) {
	maxVelocity.setX(newMaxXVelocity);
}

void GraphicBody::setMaxYVelocity(float newMaxYVelocity) {
	maxVelocity.setY(newMaxYVelocity);
}

const Vec2& GraphicBody::getMaxVelocity() const {
	return maxVelocity;
}

float GraphicBody::getMaxXVelocity() const {
	return maxVelocity.getX();
}

float GraphicBody::getMaxYVelocity() const {
	return maxVelocity.getY();
}

void GraphicBody::setCollidableSides(Side::Enum collidableSides) {
	this->collidableSides = collidableSides;
}

Side::Enum GraphicBody::getCollidableSides() {
	return collidableSides;
}

bool GraphicBody::isCollidingSide(Side::Enum sides) {
	return collidableSides & sides;
}

bool GraphicBody::getIsStatic() const {
	return staticObject;
}

void GraphicBody::setIsStatic(bool isStatic) {
	staticObject = isStatic;
}
float GraphicBody::getElasticity() const {
	return elasticity;
}
void GraphicBody::setElasticity(float newElasticity) {
	elasticity = newElasticity;
}

bool GraphicBody::solveXCollision(GraphicBody* object1, GraphicBody* object2, CollisionData* collisionInfo) {
	//We check if both instance are static
	if(object1->getIsStatic() && object2->getIsStatic()) {
		return false;
	}

	//We calculate object delta
	float overlap = 0.0f;
	float obj1Delta = object1->getXPosition() - object1->getOldXPosition();
	float obj2Delta = object2->getXPosition() - object2->getOldXPosition();

	if(obj1Delta != obj2Delta) {
		// We calculate absolute delta
		float obj1DeltaAbs = fabs(obj1Delta);
		float obj2DeltaAbs = fabs(obj2Delta);

		// We create AABBs of the old position with the updated horizontal
		//position.
		AABB obj1AABB(object1->getXPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)),
		              object1->getXPosition() + object1->getWidth() + obj1DeltaAbs,
		              object1->getOldYPosition(),
		              object1->getOldYPosition() + object1->getHeight());

		AABB obj2AABB(object2->getXPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)),
		              object2->getXPosition() + object2->getWidth() + obj2DeltaAbs,
		              object2->getOldYPosition(),
		              object2->getOldYPosition() + object2->getHeight());

		if(obj1AABB.overlaps(obj2AABB)) {

			float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + RB_OVERLAP_BIAS;

			if(obj1Delta > obj2Delta) {
				overlap = object1->getXPosition() + object1->getWidth() - object2->getXPosition();

				if(overlap > maxOverlap || !object1->isCollidingSide(Side::RIGHT) || !object2->isCollidingSide(Side::LEFT)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::RIGHT;
					collisionInfo->sideObj2 |= Side::LEFT;
				}

			} else if(obj1Delta < obj2Delta) {
				overlap = object1->getXPosition() - object2->getWidth() - object2->getXPosition();

				if((-overlap > maxOverlap) || !object1->isCollidingSide(Side::LEFT) || !object2->isCollidingSide(Side::RIGHT)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::LEFT;
					collisionInfo->sideObj2 |= Side::RIGHT;
				}
			}
		}
	}

	if(overlap) {
		float obj1v = object1->getVelocity().getX();
		float obj2v = object2->getVelocity().getX();

		if(!object1->getIsStatic() && !object2->getIsStatic()) {
			overlap *= 0.5f;

			object1->moveX(-overlap);
			object2->moveX(overlap);

			float average = (obj2v + obj2v) * 0.5f;

			object1->setXVelocity(average + (obj2v - average) * object1->getElasticity());
			object2->setXVelocity(average + (obj1v - average) * object2->getElasticity());
		} else if(!object1->getIsStatic()) {
			object1->moveX(-overlap);
			object1->setXVelocity(obj2v - (obj1v * object1->getElasticity()));

		} else if(!object2->getIsStatic()) {
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
	if(object1->getIsStatic() && object2->getIsStatic()) {
		return false;
	}

	//We calculate object delta
	float overlap = 0.0f;
	float obj1Delta = object1->getYPosition() - object1->getOldYPosition();
	float obj2Delta = object2->getYPosition() - object2->getOldYPosition();

	//We calculate absolute delta
	float obj1DeltaAbs = fabs(obj1Delta);
	float obj2DeltaAbs = fabs(obj2Delta);


	if(obj1Delta != obj2Delta) {
		// We create AABBs of the old position with the updated vertical
		// position.
		AABB obj1AABB(object1->getXPosition(),
		              object1->getXPosition() + object1->getWidth(),
		              object1->getYPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)),
		              object1->getYPosition() + object1->getHeight() + obj1DeltaAbs);

		AABB obj2AABB(object2->getXPosition(),
		              object2->getXPosition() + object2->getWidth(),
		              object2->getYPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)),
		              object2->getYPosition() + object2->getHeight() + obj2DeltaAbs);


		if(obj1AABB.overlaps(obj2AABB)) {
			float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + RB_OVERLAP_BIAS;

			if(obj1Delta > obj2Delta) {
				overlap = object1->getYPosition() + object1->getHeight() - object2->getYPosition();

				if(overlap > maxOverlap || !object1->isCollidingSide(Side::BOTTOM) || !object2->isCollidingSide(Side::TOP)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::BOTTOM;
					collisionInfo->sideObj2 |= Side::TOP;
				}

			} else if(obj1Delta < obj2Delta) {
				overlap = object1->getYPosition() - object2->getHeight() - object2->getYPosition();

				if((-overlap > maxOverlap) || !object1->isCollidingSide(Side::TOP) || !object2->isCollidingSide(Side::BOTTOM)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::TOP;
					collisionInfo->sideObj2 |= Side::BOTTOM;
				}
			}

		}
	}

	if(overlap != 0) {
		float obj1v = object1->getVelocity().getY();
		float obj2v = object2->getVelocity().getY();

		if(!object1->getIsStatic() && !object2->getIsStatic()) {
			overlap *= 0.5f;
			object1->moveY(-overlap);
			object2->moveY(overlap);

			float average = (obj1v + obj2v) * 0.5;

			object1->setYVelocity(average + (obj2v - average) * object1->getElasticity());
			object2->setYVelocity(average + (obj1v - average) * object2->getElasticity());

		} else if(!object1->getIsStatic()) {
			object1->moveY(-overlap);
			object1->setYVelocity(obj2v - (obj1v * object1->getElasticity()));

			//Handle horizontal moving static object EX. moving platform
			if(obj1Delta > obj2Delta) {
				object1->setXPosition(object1->getXPosition() + (object2->getXPosition() - object2->getOldXPosition()));
			}

		} else if(!object2->getIsStatic()) {
			object2->moveY(overlap);
			object2->setYVelocity(obj1v - (obj2v * object2->getElasticity()));

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

std::pair<bool, CollisionData> GraphicBody::collide(GraphicBody* object1, GraphicBody* object2) {
	CollisionData currentCollisionData;
	currentCollisionData.obj1 = object1;
	currentCollisionData.obj2 = object2;

	if(object1 != object2) {
		bool collideInX = solveXCollision(object1, object2, &currentCollisionData);
		bool collideInY = solveYCollision(object1, object2, &currentCollisionData);
		return std::pair<bool, CollisionData>(collideInX || collideInY, currentCollisionData);
	} else {
		return std::pair<bool, CollisionData>(false, currentCollisionData);
	}
}


std::pair<bool, CollisionData> GraphicBody::collide(GraphicBody* aGraphicBody) {
	return collide(this, aGraphicBody);
}


std::pair<bool, std::list<CollisionData> > GraphicBody::collide(std::list<GraphicBody*> GraphicBodys1, std::list<GraphicBody*> GraphicBodys2) {
	std::list<CollisionData> collisionInfo;
	bool collide = false;

	for(std::list<GraphicBody*>::iterator i = GraphicBodys1.begin(); i != GraphicBodys1.end();
	        i++) {
		for(std::list<GraphicBody*>::iterator j = GraphicBodys2.begin(); j != GraphicBodys2.end();
		        j++) {
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

std::pair<bool, std::list<CollisionData> > GraphicBody::collide(std::list<GraphicBody*> GraphicBodys) {
	std::list<CollisionData> collisionInfo;
	bool collide = false;

	for(std::list<GraphicBody*>::iterator i = GraphicBodys.begin(); i != GraphicBodys.end();
	        i++) {
		std::pair<bool, CollisionData> collisionPair = this->collide(*i);

		if(collisionPair.first) {
			collide = true;
		}

		collisionInfo.push_back(collisionPair.second);
	}

	return std::pair<bool, std::list<CollisionData> >(collide,  collisionInfo);
}


AABB GraphicBody::getAABB() const {
	return AABB(getXPosition(), getXPosition() + getWidth(), getYPosition(), getYPosition() + getHeight());
}

void GraphicBody::setDrag(const Vec2& newDrag) {
	drag = newDrag;
}

const Vec2& GraphicBody::getDrag() const {
	return drag;
}

void GraphicBody::setScaling(const Vec2& newScaling) {
	setScaling(newScaling.getX(), newScaling.getY());
}

void GraphicBody::setScaling(float xScaling, float yScaling) {
	scaling.setX(xScaling);
	scaling.setY(yScaling);
}

void GraphicBody::addToScaling(const Vec2& scalingToAdd) {
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

void GraphicBody::setXScaling(float newXScaling) {
	setScaling(newXScaling, scaling.getY());
}

void GraphicBody::setYScaling(float newYScaling) {
	setScaling(scaling.getX(), newYScaling);
}

const Vec2& GraphicBody::getScaling() const {
	return scaling;
}

float GraphicBody::getXScaling() const {
	return scaling.getX();
}

float GraphicBody::getYScaling() const {
	return scaling.getY();
}

float GraphicBody::getAngle() const {
	return angle;
}

void GraphicBody::setAngle(float newAngle) {
	angle = fmodf(newAngle, 360.0f);
}

void GraphicBody::addToAngle(float angleToAdd) {
	setAngle(angle + angleToAdd);
}

bool GraphicBody::horizLineCollide(GraphicBody* aGraphicBody, float linePosition, float lowerXBoundary, float higherXBoundary) {
	bool colliding = false;

	float delta = aGraphicBody->getYPosition() - aGraphicBody->getOldYPosition();

	float deltaABS = fabsf(delta);
	float overlap = 0.0f;

	AABB rect(aGraphicBody->getOldXPosition(),
	          aGraphicBody->getOldXPosition() + aGraphicBody->getWidth(),
	          aGraphicBody->getYPosition() - ((delta > 0.0f) ? (delta) : (0.0f)),
	          aGraphicBody->getYPosition() + aGraphicBody->getHeight() + deltaABS);


	if(rect.horizLineOverlaps(linePosition, lowerXBoundary, higherXBoundary)) {
		if(delta > 0.0f) {
			overlap = aGraphicBody->getYPosition() + aGraphicBody->getHeight() - linePosition;
		} else if(delta < 0.0f) {
			overlap = aGraphicBody->getYPosition() - linePosition;

		}

		if(overlap) {
			float objv = aGraphicBody->getVelocity().getY();
			aGraphicBody->moveY(-overlap);
			aGraphicBody->setYVelocity(-(objv * aGraphicBody->getElasticity()));
			colliding = true;
		}
	}

	return colliding;
}
bool GraphicBody::vertLineCollide(GraphicBody* aGraphicBody, float linePosition, float lowerYBoundary, float higherYBoundary) {
	bool colliding = false;
	float delta = aGraphicBody->getXPosition() - aGraphicBody->getOldXPosition();

	float deltaABS = fabsf(delta);
	float overlap = 0.0f;

	AABB rect(aGraphicBody->getXPosition() - ((delta > 0.0f) ? (delta) : (0.0f)),
	          aGraphicBody->getXPosition() + aGraphicBody->getWidth() + deltaABS,
	          aGraphicBody->getOldYPosition(),
	          aGraphicBody->getOldYPosition() + aGraphicBody->getHeight());


	if(rect.vertLineOverlaps(linePosition, lowerYBoundary, higherYBoundary)) {
		if(delta > 0.0f) {
			overlap = aGraphicBody->getXPosition() + aGraphicBody->getWidth() - linePosition;
		} else if(delta < 0.0f) {
			overlap = aGraphicBody->getXPosition() - linePosition;

		}

		if(overlap) {
			float objv = aGraphicBody->getVelocity().getX();
			aGraphicBody->moveX(-overlap);
			aGraphicBody->setXVelocity(-(objv * aGraphicBody->getElasticity()));
			colliding = true;
		}
	}

	return colliding;
}

bool GraphicBody::horizLineCollide(float linePosition, float lowerXBoundary, float higherXBoundary) {
	return horizLineCollide(this, linePosition, lowerXBoundary, higherXBoundary);
}

bool GraphicBody::vertLineCollide(float linePosition, float lowerYBoundary, float higherYBoundary) {
	return vertLineCollide(this, linePosition, lowerYBoundary, higherYBoundary);
}

void GraphicBody::copyFrom(const GraphicBody& src) {
	if(this != &src && &src) {
		position = src.position;
		oldPosition = position;
		velocity = Vec2();
		acceleration = src.acceleration;
		drag = src.drag;
		maxVelocity = src.maxVelocity;
		scaling = src.scaling;
		angle = src.angle;
		layer = src.layer;
		toBeDeleted = false;
		layerChanged = true;
		isInState = false;
		staticObject = src.staticObject;
	}
}

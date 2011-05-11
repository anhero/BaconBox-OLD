#include "GraphicBody.h"
#include "Engine.h"

#include <cmath>

#define RB_OVERLAP_BIAS 4

using namespace RedBox;
GraphicBody::GraphicBody() : Object(), maxVelocityX(NO_MAX_VELOCITY),
	maxVelocityY(NO_MAX_VELOCITY), layer(Layer()), toBeDeleted(false), layerChanged(false),
	isInState(false), collidableSides(Side::ALL), elasticity(0.0),
	staticObject(false), drag(Vec2()) {
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

void GraphicBody::copyFrom(const GraphicBody& src) {
	if(this != &src && &src) {
		position = src.position;
		oldPosition = position;
		velocity = Vec2();
		acceleration = src.acceleration;
		drag = src.drag;
		maxVelocityX = src.maxVelocityX;
		maxVelocityY = src.maxVelocityY;
		layer = src.layer;
		toBeDeleted = false;
		layerChanged = true;
		isInState = false;
		staticObject = src.staticObject;
	}
}

void GraphicBody::setVelocity(const Vec2& velocity) {
	this->velocity = velocity;
}

const Vec2& GraphicBody::getVelocity() {
	return velocity;
}
void GraphicBody::setAcceleration(const Vec2& acceleration) {
	this->acceleration = acceleration;
}
const Vec2& GraphicBody::getAcceleration() {
	return acceleration;
}

float GraphicBody::getXPosition() const {
	return position.getX();
}

float GraphicBody::getYPosition() const {
	return position.getY();
}

const Vec2& GraphicBody::getPosition() const {
	return position;
}

void GraphicBody::setXPosition(float x) {
	position.setX(x);
}

void GraphicBody::setYPosition(float y) {
	position.setY(y);
}

void GraphicBody::setPosition(float x, float y) {
	position.setX(x);
	position.setY(y);
}

void GraphicBody::setPosition(const Vec2 &newPosition) {
	setPosition(newPosition.getX(), newPosition.getY());
}

void GraphicBody::moveX(float deltaX) {
	position.setX(position.getX() + deltaX);
}

void GraphicBody::moveY(float deltaY) {
	position.setY(position.getY() + deltaY);
}

void GraphicBody::move(float deltaX, float deltaY) {
	moveX(deltaX);
	moveY(deltaY);
}

void GraphicBody::setMaxVelocityX(float xVelocity) {
	maxVelocityX = xVelocity;
}
void GraphicBody::setMaxVelocityY(float yVelocity) {
	maxVelocityY = yVelocity;
}

void GraphicBody::setMaxVelocity(float xVelocity, float yVelocity) {
	maxVelocityX = xVelocity;
	maxVelocityY = yVelocity;
}
float GraphicBody::getMaxVelocityX() {
	return maxVelocityX;
}
float GraphicBody::getMaxVelocityY() {
	return maxVelocityY;
}

void GraphicBody::setVelocityX(float xVelocity) {
	velocity.setX(xVelocity);
}
void GraphicBody::setVelocityY(float yVelocity) {
	velocity.setY(yVelocity);
}

void GraphicBody::update() {
	float ratio = Engine::getSinceLastUpdate();
	oldPosition = position;


	if(maxVelocityX != NO_MAX_VELOCITY) {

		if(velocity.getX() < -maxVelocityX) {
			velocity.setX(-maxVelocityX);
		} else if(velocity.getX() > maxVelocityX) {
			velocity.setX(maxVelocityX);
		}
	}

	if(maxVelocityY != NO_MAX_VELOCITY) {

		if(velocity.getY() < -maxVelocityY) {
			velocity.setY(-maxVelocityY);
		} else if(velocity.getY() > maxVelocityY) {
			velocity.setY(maxVelocityY);
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


void GraphicBody::setCollidableSides(Side::Enum collidableSides) {
	this->collidableSides = collidableSides;
}

Side::Enum GraphicBody::getCollidableSides() {
	return collidableSides;
}

bool GraphicBody::IsCollidingSide(Side::Enum sides) {
	return collidableSides & sides;
}

bool GraphicBody::getIsStatic() {
	return staticObject;
}

void GraphicBody::setIsStatic(bool isStatic) {
	staticObject = isStatic;
}
float GraphicBody::getElasticity() {
	return elasticity;
}
void GraphicBody::setElasticity(float elasticity) {
	this->elasticity = elasticity;
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

				if(overlap > maxOverlap || !object1->IsCollidingSide(Side::RIGHT) || !object2->IsCollidingSide(Side::LEFT)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::RIGHT;
					collisionInfo->sideObj2 |= Side::LEFT;
				}

			} else if(obj1Delta < obj2Delta) {
				overlap = object1->getXPosition() - object2->getWidth() - object2->getXPosition();

				if((-overlap > maxOverlap) || !object1->IsCollidingSide(Side::LEFT) || !object2->IsCollidingSide(Side::RIGHT)) {
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

			object1->setVelocityX(average + (obj2v - average) * object1->getElasticity());
			object2->setVelocityX(average + (obj1v - average) * object2->getElasticity());
		} else if(!object1->getIsStatic()) {
			object1->moveX(-overlap);
			object1->setVelocityX(obj2v - (obj1v * object1->getElasticity()));

		} else if(!object2->getIsStatic()) {
			object2->moveX(overlap);
			object2->setVelocityX(obj1v - (obj2v * object2->getElasticity()));
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

				if(overlap > maxOverlap || !object1->IsCollidingSide(Side::BOTTOM) || !object2->IsCollidingSide(Side::TOP)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::BOTTOM;
					collisionInfo->sideObj2 |= Side::TOP;
				}

			} else if(obj1Delta < obj2Delta) {
				overlap = object1->getYPosition() - object2->getHeight() - object2->getYPosition();

				if((-overlap > maxOverlap) || !object1->IsCollidingSide(Side::TOP) || !object2->IsCollidingSide(Side::BOTTOM)) {
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

			object1->setVelocityY(average + (obj2v - average) * object1->getElasticity());
			object2->setVelocityY(average + (obj1v - average) * object2->getElasticity());

		} else if(!object1->getIsStatic()) {
			object1->moveY(-overlap);
			object1->setVelocityY(obj2v - (obj1v * object1->getElasticity()));

			//Handle horizontal moving static object EX. moving platform
			if(obj1Delta > obj2Delta) {
				object1->setXPosition(object1->getXPosition() + (object2->getXPosition() - object2->getOldXPosition()));
			}

		} else if(!object2->getIsStatic()) {
			object2->moveY(overlap);
			object2->setVelocityY(obj1v - (obj2v * object2->getElasticity()));

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


float GraphicBody::getOldXPosition() {
	return oldPosition.getX();
}
float GraphicBody::getOldYPosition() {
	return oldPosition.getY();

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


AABB GraphicBody::getAABB() {
	return AABB(getXPosition(), getXPosition() + getWidth(), getYPosition(), getYPosition() + getHeight());
}

void GraphicBody::setDrag(const Vec2& newDrag) {
	drag = newDrag;
}

const Vec2& GraphicBody::getDrag() const {
	return drag;
}

void GraphicBody::setAccelerationX(float xAccelaration) {
	acceleration.setX(xAccelaration);
}
void GraphicBody::setAccelerationY(float yAccelaration) {
	acceleration.setY(yAccelaration);

}


float GraphicBody::getAccelerationX() {
	return acceleration.getX();
}
float GraphicBody::getAccelerationY() {
	return acceleration.getY();
}
float GraphicBody::getVelocityX() {
	return velocity.getX();
}
float GraphicBody::getVelocityY() {
	return velocity.getY();
}


bool GraphicBody::horizLineCollide(GraphicBody * aGraphicBody, float linePosition, float lowerXBoundary, float higherXBoundary){
	bool colliding = false;

	float delta = aGraphicBody->getYPosition() - aGraphicBody->getOldYPosition();

	float deltaABS = fabsf(delta);
	float overlap = 0.0f;
	
	AABB rect(aGraphicBody->getOldXPosition(),
			  aGraphicBody->getOldXPosition() + aGraphicBody->getWidth(),
			  aGraphicBody->getYPosition() - ((delta > 0.0f) ? (delta) : (0.0f)),
			  aGraphicBody->getYPosition() + aGraphicBody->getHeight() + deltaABS);
	
	
	if(rect.horizLineOverlaps(linePosition, lowerXBoundary, higherXBoundary)){
		if(delta > 0.0f) {
			overlap = aGraphicBody->getYPosition() + aGraphicBody->getHeight() - linePosition;
		}
		else if(delta < 0.0f) {
			overlap = aGraphicBody->getYPosition() - linePosition;
			
		}
		
		if(overlap){
			float objv = aGraphicBody->getVelocity().getY();
			aGraphicBody->moveY(-overlap);
			aGraphicBody->setVelocityY(-(objv * aGraphicBody->getElasticity()));
			colliding = true;
		}
	}
	return colliding;
}
bool GraphicBody::vertLineCollide(GraphicBody * aGraphicBody, float linePosition, float lowerYBoundary, float higherYBoundary){
	bool colliding = false;
	float delta = aGraphicBody->getXPosition() - aGraphicBody->getOldXPosition();
	
	float deltaABS = fabsf(delta);
	float overlap = 0.0f;
	
	AABB rect(aGraphicBody->getXPosition() - ((delta > 0.0f) ? (delta) : (0.0f)),
			  aGraphicBody->getXPosition() + aGraphicBody->getWidth() + deltaABS,
			  aGraphicBody->getOldYPosition(),
			  aGraphicBody->getOldYPosition() + aGraphicBody->getHeight());
	
	
	if(rect.vertLineOverlaps(linePosition, lowerYBoundary, higherYBoundary)){
		if(delta > 0.0f) {
			overlap = aGraphicBody->getXPosition() + aGraphicBody->getWidth() - linePosition;
		}
		else if(delta < 0.0f) {
			overlap = aGraphicBody->getXPosition() - linePosition;
			
		}
		
		if(overlap){
			float objv = aGraphicBody->getVelocity().getX();
			aGraphicBody->moveX(-overlap);
			aGraphicBody->setVelocityX(-(objv * aGraphicBody->getElasticity()));
			colliding = true;
		}
	}
	return colliding;
}

bool GraphicBody::horizLineCollide(float linePosition, float lowerXBoundary, float higherXBoundary){
	return horizLineCollide(this, linePosition, lowerXBoundary, higherXBoundary);
}

bool GraphicBody::vertLineCollide(float linePosition, float lowerYBoundary, float higherYBoundary){
	return vertLineCollide(this, linePosition, lowerYBoundary, higherYBoundary);
}


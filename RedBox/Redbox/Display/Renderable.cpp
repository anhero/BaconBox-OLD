#include "Renderable.h"
#include "Engine.h"

#include <cmath>

#define RB_OVERLAP_BIAS 4

using namespace RedBox;
Renderable::Renderable(): maxVelocityX(NO_MAX_VELOCITY), maxVelocityY(NO_MAX_VELOCITY), z(0), toBeDeleted(false), zChanged(false),
isInState(false), collidableSides(Side::ALL), elasticity(0.0), staticObject(false), drag(Vec2()){
}

Renderable::Renderable(const Renderable& src) {
	copyFrom(src);
}

Renderable::~Renderable() {
}

Renderable& Renderable::operator=(const Renderable& src) {
	copyFrom(src);
	return *this;
}

int Renderable::getZ() const {
	return this->z;
}
void Renderable::setZ(int z) {
	this->z = z;
	zChanged = true;
}

bool Renderable::isToBeDeleted() const {
	return toBeDeleted;
}

bool Renderable::isZChanged() const {
	return zChanged;
}

void Renderable::setToBeDeleted(bool newToBeDeleted) {
	toBeDeleted = newToBeDeleted;
}

void Renderable::resetZChanged() {
	zChanged = false;
}

void Renderable::copyFrom(const Renderable& src) {
	if(this != &src && &src) {
		position = src.position;
		oldPosition = position;
		velocity = Vec2();
		acceleration = src.acceleration;
		drag = src.drag;
		maxVelocityX = src.maxVelocityX;
		maxVelocityY = src.maxVelocityY;
		z = src.z;
		toBeDeleted = false;
		zChanged = true;
		isInState = false;
		staticObject = src.staticObject;
	}
}

void Renderable::setVelocity(const Vec2& velocity){
	this->velocity = velocity;
}

const Vec2& Renderable::getVelocity(){
	return velocity;
}
void Renderable::setAcceleration(const Vec2& acceleration){
	this->acceleration = acceleration;
}
const Vec2& Renderable::getAcceleration(){
	return acceleration;
}

float Renderable::getXPosition() const {
	return position.getX();
}

float Renderable::getYPosition() const {
	return position.getY();
}


void Renderable::setXPosition(float x) {
	position.setX(x);
}

void Renderable::setYPosition(float y) {
	position.setY(y);
}

void Renderable::setPosition(float x, float y) {
	position.setX(x);
	position.setY(y);
}

void Renderable::moveX(float deltaX) {
	position.setX(position.getX() + deltaX);
}

void Renderable::moveY(float deltaY) {
	position.setY(position.getY() + deltaY);
}

void Renderable::move(float deltaX, float deltaY) {
	moveX(deltaX);
	moveY(deltaY);
}

void Renderable::setMaxVelocityX(float xVelocity){
	maxVelocityX = xVelocity;
}
void Renderable::setMaxVelocityY(float yVelocity){
	maxVelocityY = yVelocity;
}

void Renderable::setMaxVelocity(float xVelocity, float yVelocity){
	maxVelocityX = xVelocity;
	maxVelocityY = yVelocity;
}
float Renderable::getMaxVelocityX(){
	return maxVelocityX;
}
float Renderable::getMaxVelocityY(){
	return maxVelocityY;
}

void Renderable::setVelocityX(float xVelocity){
	velocity.setX(xVelocity);
}
void Renderable::setVelocityY(float yVelocity){
	velocity.setY(yVelocity);
}


void Renderable::update(){
	//float ratio1 = Engine::getUpdateDelta();
	//float ratio2 = Engine::getUpdateDelay();
	float ratio = Engine::getSinceLastUpdate();
	oldPosition = position;
	
	
	if (maxVelocityX != NO_MAX_VELOCITY) {
		
		if (velocity.getX() < -maxVelocityX) {
			velocity.setX(-maxVelocityX);
		}
		else if(velocity.getX() > maxVelocityX) {
			velocity.setX(maxVelocityX);
		}
	}
	if (maxVelocityY != NO_MAX_VELOCITY) {
		
		if (velocity.getY() < -maxVelocityY) {
			velocity.setY(-maxVelocityY);
		}
		else if(velocity.getY() > maxVelocityY) {
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
	
	velocity += (acceleration* ratio);
	position += (velocity * ratio);
	this->setPosition(position.getX(), position.getY());

	
}


void Renderable::setCollidableSides(RB_SIDE collidableSides){
	this->collidableSides = collidableSides;
}

RB_SIDE Renderable::getCollidableSides(){
	return collidableSides;
}

bool Renderable::IsCollidingSide(RB_SIDE sides){
	//RB_SIDE tempSides = (collidableSides | sides);
	return collidableSides & sides;
}

bool Renderable::getIsStatic(){
	return staticObject;
}

void Renderable::setIsStatic(bool isStatic){
	staticObject = isStatic;
}
float Renderable::getElasticity(){
	return elasticity;
}
void Renderable::setElasticity(float elasticity){
	this->elasticity = elasticity;
}

bool Renderable::solveXCollision(Renderable * object1, Renderable * object2, CollisionData * collisionInfo){
	//We check if both instance are static
	if (object1->getIsStatic() && object2->getIsStatic()) {
		return false;
	}
	
	//We calculate object delta
	float overlap = 0.0f;
	float obj1Delta = object1->getXPosition() - object1->getOldXPosition();
	float obj2Delta = object2->getXPosition() - object2->getOldXPosition(); 
	
	if(obj1Delta != obj2Delta){
		// We calculate absolute delta
		float obj1DeltaAbs = fabs(obj1Delta);
		float obj2DeltaAbs = fabs(obj2Delta);

		// We create AABBs of the old position with the updated horizontal
		//position.
		AABB obj1AABB(object1->getXPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)),
					  object1->getXPosition() + object1->getWidth() + ((obj1Delta > 0.0f) ? (obj1Delta) : (-obj1Delta)),
					  object1->getOldYPosition(),
					  object1->getOldYPosition() + object1->getHeight());

		AABB obj2AABB(object2->getXPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)),
					  object2->getXPosition() + object2->getWidth() + ((obj2Delta > 0.0f) ? (obj2Delta) : (-obj2Delta)),
					  object2->getOldYPosition(),
					  object2->getOldYPosition() + object2->getHeight());
		
		if(obj1AABB.overlaps(obj2AABB)){
			
			float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + RB_OVERLAP_BIAS;

			if(obj1Delta > obj2Delta) {
				overlap = object1->getXPosition() + object1->getWidth() - object2->getXPosition();

				if(overlap > maxOverlap || !object1->IsCollidingSide(Side::RIGHT) || !object2->IsCollidingSide(Side::LEFT)) {
					overlap = 0;
				} else {
					collisionInfo->sideObj1 |= Side::RIGHT;
					collisionInfo->sideObj2 |= Side::LEFT;
				}

			} else if(obj1Delta < obj2Delta){
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

		if (!object1->getIsStatic() && !object2->getIsStatic()) {
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

bool Renderable::solveYCollision(Renderable * object1, Renderable * object2, CollisionData * collisionInfo){
	//We check if both instance are static
	if (object1->getIsStatic() && object2->getIsStatic()) {
		return false;
	}
	
	//We calculate object delta
	float overlap = 0.0f;
	float obj1Delta = object1->getYPosition() - object1->getOldYPosition();
	float obj2Delta = object2->getYPosition() - object2->getOldYPosition();
	
	//We calculate absolute delta
	float obj1DeltaAbs = fabs(obj1Delta);
	float obj2DeltaAbs = fabs(obj2Delta);
	
	
	if(obj1Delta != obj2Delta){
		// We create AABBs of the old position with the updated vertical
		// position.
		AABB obj1AABB(object1->getOldXPosition(),
					  object1->getOldXPosition() + object1->getWidth(),
					  object1->getYPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)),
					  object1->getYPosition() + object1->getHeight() + obj1DeltaAbs);

		AABB obj2AABB(object2->getOldXPosition(),
					  object2->getOldXPosition() + object2->getWidth(),
					  object2->getYPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)),
					  object2->getYPosition() + object2->getHeight() + obj2DeltaAbs);

		
		if(obj1AABB.overlaps(obj2AABB)){
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
				} else{
					collisionInfo->sideObj1 |= Side::TOP;
					collisionInfo->sideObj2 |= Side::BOTTOM;
				}
			}
			
		}
	}
	
	if(overlap != 0) {
		float obj1v = object1->getVelocity().getY();
		float obj2v = object2->getVelocity().getY();

		if (!object1->getIsStatic() && !object2->getIsStatic()) {
			overlap *= 0.5f;
			object1->moveY(-overlap);
			object2->moveY(overlap);
			
			float average = ( obj1v + obj2v) * 0.5;

			object1->setVelocityY(average + (obj2v - average) * object1->getElasticity());
			object2->setVelocityY(average + (obj1v - average) * object2->getElasticity());

		} else if(!object1->getIsStatic()) {
			object1->moveY(-overlap);
			object1->setVelocityY(obj2v - (obj1v * object1->getElasticity()));
			//Handle horizontal moving static object EX. moving platform
			if(obj1Delta > obj2Delta){
				object1->setXPosition(object1->getXPosition() + (object2->getXPosition() - object2->getOldXPosition()));
			}

		} else if(!object2->getIsStatic()) {
			object2->moveY(overlap);
			object2->setVelocityY(obj1v - (obj2v * object2->getElasticity()));
			// Handle horizontal moving static object EX. moving platform
			if(obj1Delta < obj2Delta){
				object2->setXPosition(object2->getXPosition() + object1->getXPosition() - object1->getOldXPosition());

			}
		}
		return true;
	} else {
		return false;
	}
}


std::pair<bool, CollisionData> Renderable::collide(Renderable * object1, Renderable * object2){
	CollisionData currentCollisionData;
	currentCollisionData.obj1 = object1;
	currentCollisionData.obj2 = object2;
	if (object1 != object2) {
		bool collideInX = solveXCollision(object1, object2, &currentCollisionData);
		bool collideInY = solveYCollision(object1, object2, &currentCollisionData);
		return std::pair<bool, CollisionData>(collideInX || collideInY, currentCollisionData);
	}
	else{
		return std::pair<bool, CollisionData>(false, currentCollisionData);
	}
}


std::pair<bool, CollisionData> Renderable::collide(Renderable * aRenderable){
	return collide(this, aRenderable);
}


float Renderable::getOldXPosition(){
	return oldPosition.getX();
}
float Renderable::getOldYPosition(){
	return oldPosition.getY();
	
}

std::pair<bool, std::list<CollisionData> > Renderable::collide(std::list<Renderable*> renderables1, std::list<Renderable*> renderables2){
	std::list<CollisionData> collisionInfo;
	bool collide = false;
	for(std::list<Renderable*>::iterator i = renderables1.begin(); i != renderables1.end();
		i++) {
		for(std::list<Renderable*>::iterator j = renderables2.begin(); j != renderables2.end();
			j++) {
			if(*i != *j){
				std::pair<bool, CollisionData> collisionPair = Renderable::collide(*i, *j);
				if(collisionPair.first){
					collide = true;
				}
				collisionInfo.push_back(collisionPair.second);
			}
		}
	}
	return std::pair<bool, std::list<CollisionData> >(collide,  collisionInfo);
}

std::pair<bool, std::list<CollisionData> > Renderable::collide(std::list<Renderable*> renderables){
	std::list<CollisionData> collisionInfo;
	bool collide = false;
	for(std::list<Renderable*>::iterator i = renderables.begin(); i != renderables.end();
		i++) {
		std::pair<bool, CollisionData> collisionPair = this->collide(*i);
		if(collisionPair.first){
			collide = true;
		}
		collisionInfo.push_back(collisionPair.second);
	}
	return std::pair<bool, std::list<CollisionData> >(collide,  collisionInfo);
}


AABB Renderable::getAABB(){
	return AABB(getXPosition(), getXPosition() + getWidth(), getYPosition(), getYPosition() + getHeight());
}

void Renderable::setDrag(const Vec2 &newDrag) {
	drag = newDrag;
}

const Vec2& Renderable::getDrag() const {
	return drag;
}

void Renderable::setAccelerationX(float xAccelaration){
	acceleration.setX(xAccelaration);
}
void Renderable::setAccelerationY(float yAccelaration){
	acceleration.setY(yAccelaration);

}


float Renderable::getAccelerationX(){
	return acceleration.getX();
}
float Renderable::getAccelerationY(){
	return acceleration.getY();
}
float Renderable::getVelocityX(){
	return velocity.getX();
}
float Renderable::getVelocityY(){
	return velocity.getY();
}

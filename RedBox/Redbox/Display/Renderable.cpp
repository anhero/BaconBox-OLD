#include "Renderable.h"
#include "RedBoxEngine.h"

#include <cmath>

//#define RB_OVERLAP_BIAS 0

using namespace RedBox;
Renderable::Renderable(): maxVelocityX(NO_MAX_VELOCITY), maxVelocityY(NO_MAX_VELOCITY), z(0), toBeDeleted(false), zChanged(false),
isInState(false), collidableSides(Side::ALL), elasticity(0.0), staticObject(false){
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
		acceleration = Vec2();
		maxVelocityX = src.maxVelocityX;
		maxVelocityY = src.maxVelocityY;
		z = src.z;
		toBeDeleted = false;
		zChanged = true;
		isInState = false;
	}
}

void Renderable::setVelocity(Vec2 velocity){
	this->velocity = velocity;
}

Vec2 Renderable::getVelocity(){
	return velocity;
}
void Renderable::setAcceleration(Vec2 acceleration){
	this->acceleration = acceleration;
}
Vec2 Renderable::getAcceleration(){
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
	//float ratio1 = RedBoxEngine::getUpdateDelta();
	//float ratio2 = RedBoxEngine::getUpdateDelay();
	float ratio = RedBoxEngine::getUpdateDelta();
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
	
	
	position += (velocity * ratio);
	this->setPosition(position.getX(), position.getY());
	velocity += (acceleration* ratio);
	
}


void Renderable::setCollidableSides(RB_SIDE collidableSides){
	this->collidableSides = collidableSides;
}

RB_SIDE Renderable::getCollidableSides(){
	return collidableSides;
}

bool Renderable::IsCollidingSide(RB_SIDE sides){
	RB_SIDE tempSides = (collidableSides | sides);
	return collidableSides == tempSides;
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
	float overlap = 0;
	float obj1Delta = object1->getXPosition() - object1->getOldXPosition();
	float obj2Delta = object2->getXPosition() - object2->getOldXPosition(); 
	
	//We calculate absolute delta
	float obj1DeltaAbs = (obj1Delta > 0 ? obj1Delta : -obj1Delta);
	float obj2DeltaAbs = (obj2Delta > 0 ? obj2Delta : -obj2Delta);
	
	if(obj1Delta != obj2Delta){
		
		//We create AABBs of occupied space (all the space occupied by the shape from the begining of the update to now)
		//for both object and we check if they overlap
		AABB obj1AABB = object1->getAABB();
		obj1AABB.minX -= (obj1Delta ? obj1Delta : 0);
		obj1AABB.maxX += obj1DeltaAbs;
		
		AABB obj2AABB = object2->getAABB();
		obj2AABB.minX -= (obj2Delta ? obj2Delta : 0);
		obj2AABB.maxX += obj2DeltaAbs;
		
		
		if(obj1AABB.overlaps(&obj2AABB)){
		
		
		float maxOverlap = obj1DeltaAbs + obj2DeltaAbs; //+ RB_OVERLAP_BIAS;
		
		if(obj1Delta > obj2Delta) {
			overlap = object1->getXPosition() + object1->getWidth() - object2->getXPosition();
			if(overlap > maxOverlap || !object1->IsCollidingSide(Side::RIGHT) || !object2->IsCollidingSide(Side::LEFT)){
				overlap = 0;
			}
			else{
				collisionInfo->sideObj1 |= Side::RIGHT;
				collisionInfo->sideObj2 |= Side::LEFT;
			}
		}
		else if(obj1Delta < obj2Delta){
			overlap = object1->getXPosition() - object2->getWidth() - object2->getXPosition();
			if(-overlap > maxOverlap || !object1->IsCollidingSide(Side::LEFT) || !object2->IsCollidingSide(Side::RIGHT)){
				overlap = 0;
			}
			else{
				collisionInfo->sideObj1 |= Side::LEFT;
				collisionInfo->sideObj2 |= Side::RIGHT;
			}
		}
		}	
	}
	
	if(overlap !=0){
		float obj1v = object1->getVelocity().getX();
		float obj2v = object2->getVelocity().getX();
		if (!object1->getIsStatic() && !object2->getIsStatic()) {
			overlap *= 0.5f;
			object1->setXPosition( object1->getXPosition() - overlap);
			object2->setXPosition( object1->getXPosition() + overlap);
			
			float obj1velocity = obj2v * (obj2v > 0 ? 1 : -1);
			float obj2velocity = obj1v * (obj1v > 0 ? 1 : -1);
			float average = ( obj1velocity + obj2velocity) * 0.5;
			obj1velocity -= average;
			obj2velocity -= average;
			
			object1->setVelocityX(average + obj1velocity * object1->getElasticity());
			object2->setVelocityX(average + obj1velocity * object1->getElasticity());
		}
		else if(!object1->getIsStatic()){
			object1->setXPosition(object1->getXPosition() - overlap);
			object1->setVelocityX(obj2v - obj1v * object1->getElasticity());
		}
		else if(!object2->getIsStatic()){
			object2->setXPosition(object2->getXPosition() + overlap);
			object2->setVelocityX(obj1v - obj2v*object2->getElasticity());
		}
		return true;
	}
	else{
		return false;
	}
	
	
}

bool Renderable::solveYCollision(Renderable * object1, Renderable * object2, CollisionData * collisionInfo){
	//We check if both instance are static
	if (object1->getIsStatic() && object2->getIsStatic()) {
		return false;
	}
	
	//We calculate object delta
	float overlap = 0;
	float obj1Delta = object1->getYPosition() - object1->getOldYPosition();
	float obj2Delta = object2->getYPosition() - object2->getOldYPosition();
	
	//We calculate absolute delta
	float obj1DeltaAbs = (obj1Delta > 0 ? obj1Delta : -obj1Delta);
	float obj2DeltaAbs = (obj2Delta > 0 ? obj2Delta : -obj2Delta);
	
	
	if(obj1Delta != obj2Delta){
		//We create AABBs of occupied space (all the space occupied by the shape from the begining of the update to now)
		//for both object and we check if they overlap
		AABB obj1AABB = object1->getAABB();
		obj1AABB.minY -= (obj1Delta ? obj1Delta : 0);
		obj1AABB.maxY += obj1DeltaAbs;
		
		AABB obj2AABB = object2->getAABB();
		obj2AABB.minY -= (obj2Delta ? obj2Delta : 0);
		obj2AABB.maxY += obj2DeltaAbs;
		
		
		if(obj1AABB.overlaps(&obj2AABB)){

	
		
			float maxOverlap = obj1DeltaAbs + obj2DeltaAbs; //+ RB_OVERLAP_BIAS;
		
		
		
		
		if(obj1Delta > obj2Delta) {
			overlap = object1->getYPosition() + object1->getHeight() - object2->getYPosition();
			if(overlap > maxOverlap || !object1->IsCollidingSide(Side::RIGHT) || !object2->IsCollidingSide(Side::LEFT)){
				overlap = 0;
			}
			else{
				collisionInfo->sideObj1 |= Side::BOTTOM;
				collisionInfo->sideObj2 |= Side::TOP;
			}
		}
		else if(obj1Delta < obj2Delta){
			overlap = object1->getYPosition() - object2->getHeight() - object2->getYPosition();
			if(-overlap > maxOverlap || !object1->IsCollidingSide(Side::LEFT) || !object2->IsCollidingSide(Side::RIGHT)){
				overlap = 0;
			}
			else{
				collisionInfo->sideObj1 |= Side::TOP;
				collisionInfo->sideObj2 |= Side::BOTTOM;
			}
		}
		
	}
	}
	
	if(overlap !=0){
		float obj1v = object1->getVelocity().getY();
		float obj2v = object2->getVelocity().getY();
		if (!object1->getIsStatic() && !object2->getIsStatic()) {
			overlap *= 0.5f;
			object1->setYPosition( object1->getYPosition() - overlap);
			object2->setYPosition( object1->getYPosition() + overlap);
			
			float obj1velocity = obj2v * (obj2v > 0 ? 1 : -1);
			float obj2velocity = obj1v * (obj1v > 0 ? 1 : -1);
			float average = ( obj1velocity + obj2velocity) * 0.5;
			obj1velocity -= average;
			obj2velocity -= average;
			
			object1->setVelocityY(average + obj1velocity * object1->getElasticity());
			object2->setVelocityY(average + obj1velocity * object1->getElasticity());
		}
		else if(!object1->getIsStatic()){
			object1->setYPosition(object1->getYPosition() - overlap);
			object1->setVelocityY(obj2v - obj1v * object1->getElasticity());
			//Handle horizontal moving static object EX. moving platform
			if(obj1Delta > obj2Delta){
				object1->setXPosition(object1->getXPosition() + object2->getXPosition() - object2->getOldXPosition());
			}
		}
		else if(!object2->getIsStatic()){
			object2->setYPosition(object2->getYPosition() + overlap);
			object2->setVelocityY(obj1v - obj2v*object2->getElasticity());
			//Handle horizontal moving static object EX. moving platform
			object2->setXPosition(object2->getXPosition() + object1->getXPosition() - object2->getOldXPosition());

		}
		return true;
	}
	else{
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
	return std::pair<bool, CollisionData>(collideInX && collideInY, currentCollisionData);
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

AABB Renderable::getAABB(){
	return AABB(getXPosition(), getXPosition() + getWidth(), getYPosition(), getYPosition() + getHeight());
}
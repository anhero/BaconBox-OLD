#include "Renderable.h"
#include "RedBoxEngine.h"
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
	RB_SIDE tempSides = collidableSides & sides;
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


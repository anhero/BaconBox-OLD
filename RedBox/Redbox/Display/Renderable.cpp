#include "Renderable.h"
#include "RedBoxEngine.h"
using namespace RedBox;
Renderable::Renderable(): z(0), toBeDeleted(false), zChanged(false),
isInState(false){
}

Renderable::Renderable(const Renderable& src): z(src.z), 
toBeDeleted(src.toBeDeleted), zChanged(src.zChanged), isInState(false) {
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
		this->z = src.z;
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

void Renderable::update(){
	//float ratio1 = RedBoxEngine::getUpdateDelta();
	//float ratio2 = RedBoxEngine::getUpdateDelay();
	float ratio = 0.00833;
	oldPosition = position;
	position += (velocity * ratio);
	this->setPosition(position.getX(), position.getY());
	velocity += (acceleration* ratio);
}

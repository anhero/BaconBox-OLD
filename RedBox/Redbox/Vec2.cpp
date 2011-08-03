#include "Vec2.h"

#include "Console.h"

#include "MathHelper.h"

using namespace RedBox;

const Vec2 Vec2::UP = Vec2(0.0f, -1.0f);

Vec2::Vec2() : Object(), isPtr(false) {
	coordsVal.x = 0.0f;
	coordsVal.y = 0.0f;
}

Vec2::Vec2(float pX, float pY) : Object(), isPtr(false) {
	coordsVal.x = pX;
	coordsVal.y = pY;
}

Vec2::Vec2(float* pX, float* pY) : Object(), isPtr(true) {
	coordsPtr.x = pX;
	coordsPtr.y = pY;
}

Vec2::Vec2(const Vec2& src) : Object(src), isPtr(false) {
	coordsVal.x = src.getX();
	coordsVal.y = src.getY();
}

Vec2::~Vec2() {
}

float Vec2::getX() const {
	return (isPtr) ? (*(coordsPtr.x)) : (coordsVal.x);
}
float Vec2::getY() const {
	return (isPtr) ? (*(coordsPtr.y)) : (coordsVal.y);
}

float* Vec2::getXPtr() {
	return (isPtr) ? (coordsPtr.x) : (NULL);
}

float* Vec2::getYPtr() {
	return (isPtr) ? (coordsPtr.y) : (NULL);
}

void Vec2::setXPtr(float* newXPtr) {
	if(isPtr) {
		coordsPtr.x = newXPtr;
	}
}

void Vec2::setYPtr(float* newYPtr) {
	if(isPtr) {
		coordsPtr.y = newYPtr;
	}
}

void Vec2::setXYPtr(float *newXPtr, float *newYPtr) {
	if(isPtr) {
		coordsPtr.x = newXPtr;
		coordsPtr.y = newYPtr;
	}
}

void Vec2::setX(float newX) {
	if(isPtr) {
		*(coordsPtr.x) = newX;
	} else {
		coordsVal.x = newX;
	}
}

void Vec2::setY(float newY) {
	if(isPtr) {
		*(coordsPtr.y) = newY;
	} else {
		coordsVal.y = newY;
	}
}

void Vec2::setXY(float newX, float newY) {
	if(isPtr) {
		*(coordsPtr.x) = newX;
		*(coordsPtr.y) = newY;
	} else {
		coordsVal.x = newX;
		coordsVal.y = newY;
	}
}

void Vec2::addToX(float xToAdd) {
	if(isPtr) {
		*(coordsPtr.x) += xToAdd;
	} else {
		coordsVal.x += xToAdd;
	}
}

void Vec2::addToY(float yToAdd) {
	if(isPtr) {
		*(coordsPtr.y) += yToAdd;
	} else {
		coordsVal.y += yToAdd;
	}
}

void Vec2::addToXY(float xToAdd, float yToAdd) {
	if(isPtr) {
		*(coordsPtr.x) += xToAdd;
		*(coordsPtr.y) += yToAdd;
	} else {
		coordsVal.x = xToAdd;
		coordsVal.y = yToAdd;
	}
}

bool Vec2::getIsPtr() const {
	return isPtr;
}

void Vec2::setIsPtr(bool newIsPtr) {
	isPtr = newIsPtr;
}

const Vec2 Vec2::operator*(float scalar) const {
	return Vec2(getX() * scalar, getY() * scalar);
}

const Vec2 Vec2::operator/(float scalar) const {
	return Vec2(getX() / scalar, getY() / scalar);
}

const Vec2 Vec2::operator+(Vec2 b) const {
	return Vec2(getX() + b.getX(), getY() + b.getY());
}

const Vec2 Vec2::operator-(Vec2 b) const {
	return Vec2(getX() - b.getX(), getY() - b.getY());
}

const Vec2 Vec2::operator-() const {
	return Vec2(-getX(), -getY());
}

const float Vec2::operator*(Vec2 b) const {
	return getX() * b.getX() + getY() * b.getY();
}

Vec2& Vec2::operator=(const Vec2& b) {
	Object::operator=(b);

	if(this != &b) {
		setX(b.getX());
		setY(b.getY());
	}

	return *this;
}

Vec2& Vec2::operator+=(const Vec2& b) {
	setX(getX() + b.getX());
	setY(getY() + b.getY());
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& b) {
	setX(getX() - b.getX());
	setY(getY() - b.getY());
	return *this;
}

Vec2& Vec2::operator*=(float scalar) {
	setX(getX() * scalar);
	setY(getY() * scalar);
	return *this;
}

Vec2& Vec2::operator/=(float scalar) {
	setX(getX() / scalar);
	setY(getY() / scalar);
	return *this;
}

bool Vec2::operator==(const Vec2& b) const {
	return getX() == b.getX() && getY() == b.getY();
}

bool Vec2::operator!=(const Vec2& b) const {
	return getX() != b.getX() || getY() != b.getY();
}

float Vec2::length() const {
	return sqrtf(getX() * getX() + getY() * getY());
}

float Vec2::lengthSq() const {
	return getX() * getX() + getY() * getY();
}

void Vec2::normalize() {
	if(getX() == 0.0f && getY() == 0.0f) {
		Console::print("Normalization failed, vector has no lenght\n");
	}

	float len = 1.0f / length();

	setX(getX() * len);
	setY(getY() * len);
}

void Vec2::rotate(float angle) {
	float radians = MathHelper::degreesToRadians(angle),
	      tx = getX() * cosf(radians) + getY() * sinf(radians),
	      ty = getY() * cosf(radians) - getX() * sinf(radians);
	setX(tx);
	setY(ty);
}

void Vec2::setLength(float length) {
	normalize();
	setX(getX() * length);
	setY(getY() * length);
}

void Vec2::copyFrom(const Vec2& src) {
	if(this != &src && &src) {
		isPtr = false;
		coordsVal.x = src.getX();
		coordsVal.y = src.getY();
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Vec2& v)  {
		output << "{";

		if(v.isPtr) {
			output << "isPtr: true, coordsPtr.x:" << v.coordsPtr.x << "(" << *(v.coordsPtr.x) << "f), coordsPtr.y:" <<
			       v.coordsPtr.y << "(" << *(v.coordsPtr.y) << "f)}";
		} else {
			output << "isPtr: false, coordsVal.x:" << v.coordsVal.x << "f, coordsVal.y:" << v.coordsVal.y << "f)}";
		}

		return output;  // for multiple << operators.
	}
}

#include "AABB.h"

using namespace RedBox;

AABB::AABB(): Object(), minX(0.0f), maxX(0.0f), minY(0.0f), maxY(0.0f) {
}

AABB::AABB(float newMinX, float newMaxX, float newMinY, float newMaxY) :
	Object(), minX(newMinX), maxX(newMaxX), minY(newMinY), maxY(newMaxY) {
}

AABB::AABB(const AABB& src) : Object(src), minX(src.minX), maxX(src.maxX),
	minY(src.minY), maxY(src.maxY) {
}

AABB& AABB::operator=(const AABB& src) {
	Object::operator=(src);

	if(this != &src) {
		minX = src.minX;
		maxX = src.maxX;
		minY = src.minY;
		maxY = src.maxY;
	}
	return *this;
}

bool AABB::overlaps(const AABB& rect) const {
	return overlaps(*this, rect);
}

bool AABB::overlaps(const Vec2& point) const {
	return overlaps(point.getX(), point.getY(), *this);
}

bool AABB::overlaps(float x, float y) const {
	return overlaps(x, y, *this);
}

bool AABB::overlaps(const AABB& rect1, const AABB& rect2) {
	return rect1.maxX > rect2.minX &&
	       rect1.minX < rect2.maxX &&
	       rect1.maxY > rect2.minY &&
	       rect1.minY < rect2.maxY;
}

bool AABB::overlaps(float x, float y, const AABB& rect) {
	return x > rect.minX &&
	       x < rect.maxX &&
	       y > rect.minY &&
	       y < rect.maxY;
}

bool AABB::overlaps(const Vec2& point, const AABB& rect) {
	return overlaps(point.getX(), point.getY(), rect);
}



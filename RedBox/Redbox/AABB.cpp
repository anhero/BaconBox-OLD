#include "AABB.h"

using namespace RedBox;

AABB::AABB(float newMinX, float newMaxX, float newMinY, float newMaxY) :
minX(newMinX), maxX(newMaxX), minY(newMinY), maxY(newMaxY) {
}

bool AABB::overlaps(const AABB& rect) const {
	return overlaps(*this, rect);
}

bool AABB::overlaps(const Vec2 &point) const {
	return overlaps(point.getX(), point.getY(), *this);
}

bool AABB::overlaps(float x, float y) const {
	return overlaps(x, y, *this);
}

bool AABB::overlaps(const AABB& rect1, const AABB& rect2){
	return rect1.maxX > rect2.minX &&
		   rect1.minX < rect2.maxX &&
		   rect1.maxY > rect2.minY &&
		   rect1.minY < rect2.maxY;
}

bool AABB::overlaps(float x, float y, const AABB &rect) {
	return x > rect.minX && x < rect.maxX && y > rect.minX && y < rect.maxY;
}

bool AABB::overlaps(const Vec2& point, const AABB& rect) {
	return overlaps(point.getX(), point.getY(), rect);
}



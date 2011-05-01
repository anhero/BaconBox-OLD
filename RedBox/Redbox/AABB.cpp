#include "AABB.h"

using namespace RedBox;

AABB::AABB(float minX, float maxX, float minY, float maxY){
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;

}

bool AABB::overlaps(AABB * rect1, AABB * rect2){
	return rect1->maxX > rect2->minX &&
		   rect1->minX < rect2->maxX &&
		   rect1->maxY > rect2->minY &&
		   rect1->minX < rect2->maxY;
}

bool AABB::overlaps(AABB * rect){
	return overlaps(this, rect);
}

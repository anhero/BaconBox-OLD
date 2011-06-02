#include "Layer.h"

using namespace RedBox;

bool Layer::LessCompare::operator() (const Layer& l1, const Layer& l2) {
	return (l1.getZ() < l2.getZ()) ? (true) : ((l1.getZ() > l2.getZ()) ? (false) : (l1.getScrollFactor().getX() >= l2.getScrollFactor().getX()));
}

Layer::Layer() : Object(), z(0), scrollFactor(Vec2(1.0f, 1.0f)) {
}

Layer::Layer(int newZ, const Vec2& newScrollFactor) : Object(), z(newZ),
	scrollFactor(newScrollFactor) {
}

Layer::Layer(const Layer &src) : Object(src), z(src.z),
	scrollFactor(src.scrollFactor) {
}

Layer& Layer::operator=(const Layer& src) {
	Object::operator=(src);
	if(this != &src) {
		z = src.z;
		scrollFactor = src.scrollFactor;
	}
}

bool Layer::operator==(const Layer& other) {
	return z == other.z && scrollFactor == other.scrollFactor;
}

bool Layer::operator!=(const Layer& other) {
	return !(*this == other);
}

int Layer::getZ() const {
	return z;
}

void Layer::setZ(int newZ) {
	z = newZ;
}

const Vec2& Layer::getScrollFactor() const {
	return scrollFactor;
}

void Layer::setScrollFactor(const Vec2& newScrollFactor) {
	scrollFactor = newScrollFactor;
}

float Layer::getXScrollFactor() const {
	return scrollFactor.getX();
}

void Layer::setXScrollFactor(float newXScrollFactor) {
	scrollFactor.setX(newXScrollFactor);
}

float Layer::getYScrollFactor() const {
	return scrollFactor.getY();
}

void Layer::setYScrollFactor(float newYScrollFactor) {
	scrollFactor.setY(newYScrollFactor);
}

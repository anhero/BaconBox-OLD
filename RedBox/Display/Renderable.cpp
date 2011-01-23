#include "Renderable.h"

using namespace RedBox;
Renderable::Renderable(): z(0), toBeDeleted(false), zChanged(false) {
}

Renderable::Renderable(const Renderable& src): z(src.z), 
toBeDeleted(src.toBeDeleted), zChanged(src.zChanged) {
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

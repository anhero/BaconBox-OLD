#include "Renderable.h"

using namespace RedBox;
Renderable::Renderable(): z(0) {
}
Renderable::Renderable(const Renderable& src): z(src.z) {
}

Renderable::~Renderable() {
}

void Renderable::copyFrom(const Renderable& src) {
	if(this != &src && &src) {
		this->z = src.z;
	}
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
}

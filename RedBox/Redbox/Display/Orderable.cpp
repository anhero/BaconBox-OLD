#include "Orderable.h"

namespace RedBox {
	Orderable::Orderable() : z(0) {
	}

	Orderable::Orderable(const Orderable &src) : z(src.z) {
	}

	Orderable::~Orderable() {
	}

	Orderable &Orderable::operator=(const Orderable &src) {
		if(this != &src) {
			z = src.z;
		}
		return *this;
	}

	int Orderable::getZ() const {
		return z;
	}

	void Orderable::setZ(int newZ) {
		z = newZ;
	}
}

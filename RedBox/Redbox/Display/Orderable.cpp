#include "Orderable.h"

namespace RedBox {
	bool Orderable::LessCompare::operator()(const Orderable *o1,
	                                        const Orderable *o2) {
		return o1 && o2 && o1->getZ() < o2->getZ();
	}

	Orderable::Orderable() : z(0) {
	}

	Orderable::Orderable(const Orderable &src) : z(src.z) {
	}

	Orderable::~Orderable() {
	}

	Orderable &Orderable::operator=(const Orderable &src) {
		if (this != &src) {
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

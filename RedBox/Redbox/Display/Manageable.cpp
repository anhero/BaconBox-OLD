#include "Manageable.h"

namespace RedBox {
	Manageable::Manageable() : managed(false), toBeDeleted(false) {
	}

	Manageable::Manageable(const Manageable &src) : managed(false),
		toBeDeleted(src.toBeDeleted) {
	}

	Manageable::~Manageable() {
	}

	Manageable &Manageable::operator=(const Manageable &src) {
		if (this != &src) {
			toBeDeleted = src.toBeDeleted;
		}

		return *this;
	}

	bool Manageable::isManaged() const {
		return managed;
	}

	void Manageable::setManaged(bool newManaged) {
		managed = newManaged;
	}

	bool Manageable::isToBeDeleted() const {
		return toBeDeleted;
	}

	void Manageable::setToBeDeleted(bool newToBeDeleted) {
		toBeDeleted = newToBeDeleted;
	}
}

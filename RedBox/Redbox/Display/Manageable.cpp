#include "Manageable.h"

namespace RedBox {
	Manageable::Manageable() : keyChanged(false), managed(false),
		toBeDeleted(false) {
	}

	Manageable::Manageable(const Manageable &src) : keyChanged(src.keyChanged),
		managed(false), toBeDeleted(src.toBeDeleted) {
	}

	Manageable::~Manageable() {
	}

	Manageable &Manageable::operator=(const Manageable &src) {
		if (this != &src) {
			keyChanged = src.keyChanged;
			toBeDeleted = src.toBeDeleted;
		}

		return *this;
	}

	bool Manageable::isKeyChanged() const {
		return keyChanged;
	}

	bool Manageable::isManaged() const {
		return managed;
	}

	void Manageable::keyChange() {
		keyChanged = true;
	}

	void Manageable::resetKeyChanged() {
		keyChanged = false;
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

#include "Deactivable.h"

namespace RedBox {
	Deactivable::Deactivable() : Updateable(), active(true) {
	}

	Deactivable::Deactivable(const Deactivable &src) : Updateable(src),
	    active(src.active) {
	}

	Deactivable::~Deactivable() {
	}

	Deactivable &Deactivable::operator=(const Deactivable &src) {
		if (this != &src) {
			active = src.active;
		}

		return *this;
	}

	bool Deactivable::isActive() const {
		return active;
	}

	void Deactivable::setActive(bool newActive) {
		active = newActive;
	}
}

#include "Keyable.h"

namespace RedBox {
	Keyable::Keyable() : keyChanged(false) {
	}

	Keyable::Keyable(const Keyable &src) : keyChanged(src.keyChanged) {
	}

	Keyable::~Keyable() {
	}

	Keyable &Keyable::operator=(const Keyable &src) {
		if (this != &src) {
			keyChanged = src.keyChanged;
		}

		return *this;
	}

	bool Keyable::isKeyChanged() const {
		return keyChanged;
	}

	void Keyable::keyChange() {
		keyChanged = true;
	}

	void Keyable::resetKeyChanged() {
		keyChanged = false;
	}
}
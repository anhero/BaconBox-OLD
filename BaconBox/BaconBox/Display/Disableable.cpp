#include "Disableable.h"

namespace BaconBox {
	Disableable::Disableable() : Deactivable(), Hidable(), enabled(true) {
	}

	Disableable::Disableable(const Disableable &src) : Deactivable(src),
		Hidable(src), enabled(src.enabled) {
	}

	Disableable::~Disableable() {
	}

	Disableable &Disableable::operator=(const Disableable &src) {
		this->Deactivable::operator=(src);
		this->Hidable::operator=(src);

		if (this != &src) {
			enabled = src.enabled;
		}

		return *this;
	}

	bool Disableable::isEnabled() const {
		return enabled;
	}

	void Disableable::setEnabled(bool newEnabled) {
		enabled = newEnabled;
	}
}

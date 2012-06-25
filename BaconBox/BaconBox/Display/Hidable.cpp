#include "Hidable.h"

namespace BaconBox {
	Hidable::Hidable() : Maskable(), visible(true) {
	}

	Hidable::Hidable(const Hidable &src) : Maskable(src),
	    visible(src.visible) {
	}

	Hidable::~Hidable() {
	}

	Hidable &Hidable::operator=(const Hidable &src) {
		if(this != &src) {
			visible = src.visible;
		}
		return *this;
	}

	bool Hidable::isVisible() const {
		return visible;
	}

	void Hidable::setVisible(bool newVisible) {
		visible = newVisible;
	}
}

#include "Scrollable.h"

namespace BaconBox {
	Scrollable::Scrollable() : scrollFactor(1.0f, 1.0f), hud(false) {
	}

	Scrollable::Scrollable(const Scrollable &src) :
	    scrollFactor(src.scrollFactor), hud(src.hud) {
	}

	Scrollable::~Scrollable() {
	}

	Scrollable &Scrollable::operator=(const Scrollable &src) {
		if (this != &src) {
			scrollFactor = src.scrollFactor;
			hud = src.hud;
		}

		return *this;
	}

	const Vector2 &Scrollable::getScrollFactor() const {
		return scrollFactor;
	}

	void Scrollable::setScrollFactor(const Vector2 &newScrollFactor) {
		setScrollFactor(newScrollFactor.x, newScrollFactor.y);
	}

	void Scrollable::setScrollFactor(float newXScrollFactor,
	                                 float newYScrollFactor) {
		scrollFactor.x = newXScrollFactor;
		scrollFactor.y = newYScrollFactor;
	}

	float Scrollable::getXScrollFactor() const {
		return scrollFactor.x;
	}

	void Scrollable::setXScrollFactor(float newXScrollFactor) {
		setScrollFactor(newXScrollFactor, scrollFactor.y);
	}

	float Scrollable::getYScrollFactor() const {
		return scrollFactor.y;
	}

	void Scrollable::setYScrollFactor(float newYScrollFactor) {
		setScrollFactor(scrollFactor.x, newYScrollFactor);
	}

	bool Scrollable::isHud() const {
		return hud;
	}

	void Scrollable::setHud(bool newHud) {
		hud = newHud;
	}
}

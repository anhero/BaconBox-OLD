#include "Scrollable.h"

namespace RedBox {
	Scrollable::Scrollable() : scrollFactor(1.0f, 1.0f) {
	}

	Scrollable::Scrollable(const Scrollable &src) :
		scrollFactor(src.scrollFactor) {
	}

	Scrollable::~Scrollable() {
	}

	Scrollable &Scrollable::operator=(const Scrollable &src) {
		if (this != &src) {
			scrollFactor = src.scrollFactor;
		}

		return *this;
	}

	const Vector2 &Scrollable::getScrollFactor() const {
		return scrollFactor;
	}

	void Scrollable::setScrollFactor(const Vector2 &newScrollFactor) {
		setScrollFactor(newScrollFactor.getX(), newScrollFactor.getY());
	}

	void Scrollable::setScrollFactor(float newXScrollFactor,
	                                 float newYScrollFactor) {
		scrollFactor.setXY(newXScrollFactor, newYScrollFactor);
	}

	float Scrollable::getXScrollFactor() const {
		return scrollFactor.getX();
	}

	void Scrollable::setXScrollFactor(float newXScrollFactor) {
		setScrollFactor(newXScrollFactor, scrollFactor.getY());
	}

	float Scrollable::getYScrollFactor() const {
		return scrollFactor.getY();
	}

	void Scrollable::setYScrollFactor(float newYScrollFactor) {
		setScrollFactor(scrollFactor.getX(), newYScrollFactor);
	}
}

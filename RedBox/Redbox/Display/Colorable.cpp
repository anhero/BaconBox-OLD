#include "Colorable.h"

namespace RedBox {
	Colorable::Colorable(const Color &newColor) : color(newColor) {
	}

	Colorable::Colorable(const Colorable &src) : color(src.color) {
	}

	Colorable::~Colorable() {
	}

	Colorable &Colorable::operator=(const Colorable &src) {
		if (this != &src) {
			color = src.color;
		}

		return *this;
	}

	const Color &Colorable::getColor() const {
		return color;
	}

	void Colorable::setColor(const Color &newColor) {
		color = newColor;
	}

	uint8_t Colorable::getAlpha() const {
		return color.getAlpha();
	}

	void Colorable::setAlpha(int32_t newAlpha) {
		Color tmpColor = color;
		tmpColor.setAlpha(newAlpha);
		setColor(tmpColor);
	}
}

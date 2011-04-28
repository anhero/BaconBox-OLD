#include "Color.h"

using namespace RedBox;

const Color Color::BLACK = Color(0, 0, 0, Color::MAX_COMPONENT_VALUE);
const Color Color::WHITE = Color(Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);
const Color Color::RED = Color(Color::MAX_COMPONENT_VALUE, 0, 0, Color::MAX_COMPONENT_VALUE);
const Color Color::GREEN = Color(0, Color::MAX_COMPONENT_VALUE, 0, Color::MAX_COMPONENT_VALUE);
const Color Color::BLUE = Color(0, 0, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);
const Color Color::YELLOW = Color(Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, 0, Color::MAX_COMPONENT_VALUE);
const Color Color::PINK = Color(Color::MAX_COMPONENT_VALUE, 0, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);
const Color Color::TEAL = Color(0, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);

Color::Color() {
	operator=(BLACK);
}

Color::Color(unsigned int red, unsigned int green, unsigned int blue,
			 unsigned int alpha) {
	setRGBA(red, green, blue, alpha);
}

Color::Color(const Color& src) {
	if(this != &src) {
		setRGBA(src.getRed(), src.getGreen(), src.getBlue(), src.getAlpha());
	}
}

Color& Color::operator=(const Color& src) {
	if(this != &src) {
		setRGBA(src.getRed(), src.getGreen(), src.getBlue(), src.getAlpha());
	}
}

unsigned int Color::getRed() const {
	return colors[R];
}

unsigned int Color::getGreen() const {
	return colors[G];
}

unsigned int Color::getBlue() const {
	return colors[B];
}

unsigned int Color::getAlpha() const {
	return colors[A];
}

void Color::setRed(unsigned int red) {
	if(red > MAX_COMPONENT_VALUE) red = MAX_COMPONENT_VALUE;
	colors[R] = red;
}

void Color::setGreen(unsigned int green) {
	if(green > MAX_COMPONENT_VALUE) green = MAX_COMPONENT_VALUE;
	colors[G] = green;
}

void Color::setBlue(unsigned int blue) {
	if(blue > MAX_COMPONENT_VALUE) blue = MAX_COMPONENT_VALUE;
	colors[B] = blue;
}

void Color::setAlpha(unsigned int alpha) {
	if(alpha > MAX_COMPONENT_VALUE) alpha = MAX_COMPONENT_VALUE;
	colors[A] = alpha;
}

void Color::setRGB(unsigned int red, unsigned int green, unsigned int blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void Color::setRGBA(unsigned int red, unsigned int green, unsigned int blue,
					unsigned int alpha) {
	setRGB(red, green, blue);
	setAlpha(alpha);
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Color& color) {
		output << "{colors: [" << color.colors[Color::R] << ", " <<
				  color.colors[Color::G] << ", " << color.colors[Color::B] <<
				  ", " << color.colors[Color::A] << "]}";
		return output;
	}
}

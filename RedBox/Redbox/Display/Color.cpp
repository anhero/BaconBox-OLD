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

Color::Color(unsigned int rgba) {
	setRGBA(rgba);
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

Color::operator unsigned int() const {
	unsigned int result = (colors[R] & 0xff) << 24;
	result |= (colors[G] & 0xff) << 16;
	result |= (colors[B] & 0xff) << 8;
	result |= (colors[A] & 0xff);
	return result;
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
	colors[R] = (red & MAX_COMPONENT_VALUE);
}

void Color::setGreen(unsigned int green) {
	colors[G] = (green & MAX_COMPONENT_VALUE);
}

void Color::setBlue(unsigned int blue) {
	colors[B] = (blue & MAX_COMPONENT_VALUE);
}

void Color::setAlpha(unsigned int alpha) {
	colors[A] = (alpha & MAX_COMPONENT_VALUE);
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

void Color::setRGBA(unsigned int rgba) {
	setRGBA((rgba & 0xff000000) >> 24,
			(rgba & 0x00ff0000) >> 16,
			(rgba & 0x0000ff00) >> 8,
			rgba & 0x000000ff);
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Color& color) {
		output << "{colors: [" << color.colors[Color::R] << ", " <<
				  color.colors[Color::G] << ", " << color.colors[Color::B] <<
				  ", " << color.colors[Color::A] << "]}";
		return output;
	}
}

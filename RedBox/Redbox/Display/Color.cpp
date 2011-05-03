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

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	setRGBA(red, green, blue, alpha);
}

Color::Color(uint32_t rgba) {
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

bool Color::operator==(const Color& other) {
	return colors[R] == other.colors[R] && colors[G] == other.colors[G] &&
			colors[B] == other.colors[B] && colors[A] == other.colors[A];
}

bool Color::operator!=(const Color& other) {
	return !operator==(other);
}

Color::operator uint32_t() const {
	unsigned int result = static_cast<uint32_t>(colors[R]) << 24;
	result |= static_cast<uint32_t>(colors[G]) << 16;
	result |= static_cast<uint32_t>(colors[B]) << 8;
	result |= static_cast<uint32_t>(colors[A]);
	return result;
}

uint8_t Color::getRed() const {
	return colors[R];
}

uint8_t Color::getGreen() const {
	return colors[G];
}

uint8_t Color::getBlue() const {
	return colors[B];
}

uint8_t Color::getAlpha() const {
	return colors[A];
}

void Color::setRed(uint8_t red) {
	colors[R] = (red & MAX_COMPONENT_VALUE);
}

void Color::setGreen(uint8_t green) {
	colors[G] = green;
}

void Color::setBlue(uint8_t blue) {
	colors[B] = blue;
}

void Color::setAlpha(uint8_t alpha) {
	colors[A] = alpha;
}

void Color::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void Color::setRGB(uint32_t rgb) {
	setRGB(static_cast<uint8_t>((rgb & 0xff0000) >> 16),
		   static_cast<uint8_t>((rgb & 0x00ff00) >> 8),
		   static_cast<uint8_t>(rgb & 0x0000ff));
}

void Color::setRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	setRGB(red, green, blue);
	setAlpha(alpha);
}

void Color::setRGBA(uint32_t rgba) {
	setRGBA(static_cast<uint8_t>((rgba & 0xff000000) >> 24),
			static_cast<uint8_t>((rgba & 0x00ff0000) >> 16),
			static_cast<uint8_t>((rgba & 0x0000ff00) >> 8),
			static_cast<uint8_t>(rgba & 0x000000ff));
}

const uint8_t* Color::getComponents() const {
	return colors;
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Color& color) {
		output << "{colors: [" << color.colors[Color::R] << ", " <<
				  color.colors[Color::G] << ", " << color.colors[Color::B] <<
				  ", " << color.colors[Color::A] << "]}";
		return output;
	}
}

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

const float Color::UNCLAMPED_MAX = 255.0f;

Color::Color() : Object() {
	operator=(BLACK);
}

Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha) :
Object() {
	setRGBA(red, green, blue, alpha);
}

Color::Color(uint32_t rgba) : Object() {
	setRGBA(rgba);
}

Color::Color(const Color& src) : Object(src) {
	if(this != &src) {
		setRGBA(src.getRed(), src.getGreen(), src.getBlue(), src.getAlpha());
	}
}

Color& Color::operator=(const Color& src) {
	Object::operator=(src);
	if(this != &src) {
		setRGBA(src.getRed(), src.getGreen(), src.getBlue(), src.getAlpha());
	}
	return *this;
}

bool Color::operator==(const Color& other) {
	return colors[R] == other.colors[R] && colors[G] == other.colors[G] &&
			colors[B] == other.colors[B] && colors[A] == other.colors[A];
}

bool Color::operator!=(const Color& other) {
	return !operator==(other);
}

Color::operator uint32_t() const {
	unsigned int result = static_cast<uint32_t>(colors[R] * UNCLAMPED_MAX) << 24;
	result |= static_cast<uint32_t>(colors[G] * UNCLAMPED_MAX) << 16;
	result |= static_cast<uint32_t>(colors[B] * UNCLAMPED_MAX) << 8;
	result |= static_cast<uint32_t>(colors[A] * UNCLAMPED_MAX);
	return result;
}

uint8_t Color::getRed() const {
	return colors[R] * UNCLAMPED_MAX;
}

uint8_t Color::getGreen() const {
	return colors[G] * UNCLAMPED_MAX;
}

uint8_t Color::getBlue() const {
	return colors[B] * UNCLAMPED_MAX;
}

uint8_t Color::getAlpha() const {
	return colors[A] * UNCLAMPED_MAX;
}

void Color::setRed(int32_t red) {
	colors[R] = getWithinRange(red);
}

void Color::setGreen(int32_t green) {
	colors[G] = getWithinRange(green);
}

void Color::setBlue(int32_t blue) {
	colors[B] = getWithinRange(blue);
}

void Color::setAlpha(int32_t alpha) {
	colors[A] = getWithinRange(alpha);
}

void Color::setRGB(int32_t red, int32_t green, int32_t blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void Color::setRGB(uint32_t rgb) {
	setRGB(static_cast<int32_t>((rgb & 0xff0000) >> 16),
		   static_cast<int32_t>((rgb & 0x00ff00) >> 8),
		   static_cast<int32_t>(rgb & 0x0000ff));
}

void Color::setRGBA(int32_t red, int32_t green, int32_t blue, int32_t alpha) {
	setRGB(red, green, blue);
	setAlpha(alpha);
}

void Color::setRGBA(uint32_t rgba) {
	setRGBA(static_cast<int32_t>((rgba & 0xff000000) >> 24),
			static_cast<int32_t>((rgba & 0x00ff0000) >> 16),
			static_cast<int32_t>((rgba & 0x0000ff00) >> 8),
			static_cast<int32_t>(rgba & 0x000000ff));
}

const float* Color::getComponents() const {
	return colors;
}

float Color::getWithinRange(int32_t component) {
	return static_cast<float>((component < 0) ? (0) : ((component > MAX_COMPONENT_VALUE_32) ? (MAX_COMPONENT_VALUE) : (component)) ) / UNCLAMPED_MAX;
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Color& color) {
		output << "{colors: [" << color.colors[Color::R] << ", " <<
				  color.colors[Color::G] << ", " << color.colors[Color::B] <<
				  ", " << color.colors[Color::A] << "]}";
		return output;
	}
}

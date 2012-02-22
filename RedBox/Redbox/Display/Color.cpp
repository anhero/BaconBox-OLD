#include "Color.h"

#include <cmath>

namespace RedBox {
	const Color Color::BLACK = Color(0, 0, 0, Color::MAX_COMPONENT_VALUE);
	const Color Color::WHITE = Color(Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);
	const Color Color::RED = Color(Color::MAX_COMPONENT_VALUE, 0, 0, Color::MAX_COMPONENT_VALUE);
	const Color Color::GREEN = Color(0, Color::MAX_COMPONENT_VALUE, 0, Color::MAX_COMPONENT_VALUE);
	const Color Color::BLUE = Color(0, 0, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);
	const Color Color::YELLOW = Color(Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, 0, Color::MAX_COMPONENT_VALUE);
	const Color Color::PINK = Color(Color::MAX_COMPONENT_VALUE, 0, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);
	const Color Color::TEAL = Color(0, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE, Color::MAX_COMPONENT_VALUE);

	uint8_t Color::getWithinRange(int32_t component) {
		return static_cast<uint8_t>((component < 0) ? (0) : ((component > MAX_COMPONENT_VALUE_32) ? (MAX_COMPONENT_VALUE) : (component)));
	}

	Color::Color() {
		operator=(BLACK);
	}

	Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha) {
		setRGBA(red, green, blue, alpha);
	}

	Color::Color(uint32_t rgba) {
		setRGBA(rgba);
	}

	Color::Color(const Color &src) {
		if (this != &src) {
			setRGBA(src.getRed(), src.getGreen(), src.getBlue(), src.getAlpha());
		}
	}

	Color &Color::operator=(const Color &src) {
		if (this != &src) {
			setRGBA(src.getRed(), src.getGreen(), src.getBlue(), src.getAlpha());
		}

		return *this;
	}

	bool Color::operator==(const Color &other) {
		return colors[R] == other.colors[R] && colors[G] == other.colors[G] &&
		       colors[B] == other.colors[B] && colors[A] == other.colors[A];
	}

	bool Color::operator!=(const Color &other) {
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
		setRGB(static_cast<uint8_t>((rgb & 0xff0000) >> 16),
		       static_cast<uint8_t>((rgb & 0x00ff00) >> 8),
		       static_cast<uint8_t>(rgb & 0x0000ff));
	}

	void Color::setRGBA(int32_t red, int32_t green, int32_t blue, int32_t alpha) {
		setRGB(red, green, blue);
		setAlpha(alpha);
	}

	void Color::setRGBA(uint32_t rgba) {
		setRGBA(static_cast<uint8_t>((rgba & 0xff000000) >> 24),
		        static_cast<uint8_t>((rgba & 0x00ff0000) >> 16),
		        static_cast<uint8_t>((rgba & 0x0000ff00) >> 8),
		        static_cast<uint8_t>(rgba & 0x000000ff));
	}

	const uint8_t *Color::getComponents() const {
		return colors;
	}

	Color::HSV Color::getHSV() const {
		Color::HSV thisColor;

		// Sets the default saturation
		thisColor.S = 0;
		// Sets the hue
		thisColor.H = this->getHue();

		// Colors as percentage
		float red   = static_cast<float>(colors[R]) / 255.0f;
		float green = static_cast<float>(colors[G]) / 255.0f;
		float blue  = static_cast<float>(colors[B]) / 255.0f;

		// Find the max color
		float maxColor = std::max(red, std::max(green, blue));
		float minColor = std::min(red, std::min(green, blue));

		float delta = maxColor - minColor;

		// Sets the found value
		thisColor.V = maxColor;

		// When there is a saturation
		if (maxColor != 0) {
			// Sets the right saturation
			thisColor.S = delta / maxColor;
		}

		return thisColor;
	}

	void Color::setHSV(Color::HSV hsvColor) {
		// http://www.cs.rit.edu/~ncs/color/t_convert.html#RGB to HSV & HSV to RGB
		int i;

		if (hsvColor.V > 1.0f) {
			hsvColor.V = 1.0f;

		} else if (hsvColor.V < 0.0f) {
			hsvColor.V = 0.0f;
		}

		if (hsvColor.S > 1.0f) {
			hsvColor.S = 1.0f;

		} else if (hsvColor.S < 0.0f) {
			hsvColor.S = 0.0f;
		}

		float hueRemainder;
		float p;
		float q;
		float t;

		if (hsvColor.S == 0) {
			// achromatic (grey)
			colors[R] = static_cast<float>(hsvColor.V * 255.0f);
			colors[G] = static_cast<float>(hsvColor.V * 255.0f);
			colors[B] = static_cast<float>(hsvColor.V * 255.0f);
			return;
		}

		hsvColor.H /= 60; // Gives the sector of the HSV hexagon

		i = floor(hsvColor.H);
		hueRemainder = hsvColor.H - i;
		p = hsvColor.V * (1 - hsvColor.S);
		q = hsvColor.V * (1 - hsvColor.S * hueRemainder);
		t = hsvColor.V * (1 - hsvColor.S * (1 - hueRemainder));

		switch (i) {
		case 0:
			this->colors[R] = static_cast<float>((hsvColor.V) * 255.0f);
			this->colors[G] = static_cast<float>((t) * 255.0f);
			this->colors[B] = static_cast<float>((p) * 255.0f);
			break;

		case 1:
			this->colors[R] = static_cast<float>((q) * 255.0f);
			this->colors[G] = static_cast<float>((hsvColor.V) * 255.0f);
			this->colors[B] = static_cast<float>((p) * 255.0f);
			break;

		case 2:
			this->colors[R] = static_cast<float>((p) * 255.0f);
			this->colors[G] = static_cast<float>((hsvColor.V) * 255.0f);
			this->colors[B] = static_cast<float>((t) * 255.0f);
			break;

		case 3:
			this->colors[R] = static_cast<float>((p) * 255.0f);
			this->colors[G] = static_cast<float>((q) * 255.0f);
			this->colors[B] = static_cast<float>((hsvColor.V) * 255.0f);
			break;

		case 4:
			this->colors[R] = static_cast<float>((t) * 255.0f);
			this->colors[G] = static_cast<float>((p) * 255.0f);
			this->colors[B] = static_cast<float>((hsvColor.V) * 255.0f);
			break;

		default: // case 5:
			this->colors[R] = static_cast<float>((hsvColor.V) * 255.0f);
			this->colors[G] = static_cast<float>((p) * 255.0f);
			this->colors[B] = static_cast<float>((q) * 255.0f);
			break;
		}
	}

	float Color::getHue() const {
		// If this color is a shade of pure gray, black or white.
		if (colors[R] == colors[B] && colors[R] == colors[G]) {
			// Hue is returned as 0, as usual with almost every implementation.
			// In reality, Hue is undefined, though.
			return 0;
		}

		// Find dominant color
		float maxColor = static_cast<float>(std::max(colors[R], std::max(colors[G], colors[B])));
		float minColor = static_cast<float>(std::min(colors[R], std::min(colors[G], colors[B])));

		float hue;

		// Red is max
		if (maxColor == colors[R]) {
			hue = static_cast<float>(colors[G] - colors[B]) / (maxColor - minColor);
		}

		// Green is max
		else if (maxColor == colors[G]) {
			hue = static_cast<float>(colors[B] - colors[R]) / (maxColor - minColor) + 2.0f;
		}

		// Blue is max
		else {
			hue = static_cast<float>(colors[R] - colors[G]) / (maxColor - minColor) + 4.0f;
		}

		// Gets it up to 360 degrees.
		hue *= 60.0f;

		// Shifts it back to positive if negative.
		if (hue < 0) {
			hue += 360.0f;
		}

		return hue;
	}

	float Color::getSaturation() const {
		return getHSV().S;
	}

	float Color::getValue() const {
		return getHSV().V;
	}

	void Color::setHue(float hue) {
		Color::HSV color = getHSV();
		color.H = hue;
		setHSV(color);
	}

	void Color::setSaturation(float saturation) {
		Color::HSV color = getHSV();
		color.S = saturation;
		setHSV(color);
	}

	void Color::setValue(float value) {
		Color::HSV color = getHSV();
		color.V = value;
		setHSV(color);
	}

	std::ostream &operator<<(std::ostream &output, const Color &color) {
		output << "{colors: [" << static_cast<int>(color.colors[Color::R]) << ", " <<
		       static_cast<int>(color.colors[Color::G]) << ", " << static_cast<int>(color.colors[Color::B]) <<
		       ", " << static_cast<int>(color.colors[Color::A]) << "]}";
		return output;
	}
}

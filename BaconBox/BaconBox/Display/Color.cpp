#include "BaconBox/Display/Color.h"

#include <cmath>

#include <map>
#include <vector>
#include <utility>

#include "BaconBox/Helper/Serialization/Value.h"
#include "BaconBox/Helper/Serialization/DefaultSerializer.h"
#include "BaconBox/Helper/Serialization/Serializer.h"
#include "BaconBox/Helper/StringHelper.h"
#include "BaconBox/Helper/Serialization/Object.h"

namespace BaconBox {
	const Color Color::BLACK(0, 0, 0);
	const Color Color::SILVER(192, 192, 192);
	const Color Color::GRAY(128, 128, 128);
	const Color Color::WHITE(255, 255, 255);
	const Color Color::MAROON(128, 0, 0);
	const Color Color::RED(255, 0, 0);
	const Color Color::PURPLE(128, 0, 128);
	const Color Color::FUCHSIA(255, 0, 255);
	const Color Color::GREEN(0, 128, 0);
	const Color Color::LIME(0, 255, 0);
	const Color Color::OLIVE(128, 128, 0);
	const Color Color::YELLOW(255, 255, 0);
	const Color Color::NAVY(0, 0, 128);
	const Color Color::BLUE(0, 0, 255);
	const Color Color::TEAL(0, 128, 128);
	const Color Color::AQUA(0, 255, 255);
	const Color Color::TRANSPARENT(0, 0, 0, 0);

	uint8_t Color::getWithinRange(int32_t component) {
		return static_cast<uint8_t>((component < 0) ? (0) : ((component > MAX_COMPONENT_VALUE_32) ? (MAX_COMPONENT_VALUE) : (component)));
	}

	Color::Color() {
		operator=(WHITE);
	}

	Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha) {
		setRGBA(red, green, blue, alpha);
	}

	Color::Color(uint32_t rgba) {
		setRGBA(rgba);
	}

	Color::Color(const std::string &colorString) {
		operator=(WHITE);
		setRGBA(colorString);
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

	std::map<std::string, Color> createCssColorMap();

	void Color::setRGBA(const std::string &colorString) {
		static const std::map<std::string, Color> cssColorMap = createCssColorMap();
		// We remove the whitespaces.
		std::string tmp(StringHelper::toLower(colorString));
		StringHelper::trim(tmp);

		// We make sure the string is not empty.
		if (!tmp.empty()) {
			// If it's in hexadecimal.
			if (tmp[0] == '#') {
				// We remove the '#'.
				tmp.erase(0, 1);
				
				// We make sure it has a valid size.
				if (tmp.size() == 3) {
					// We convert it to the 6 char format.
					tmp.reserve(8);
					tmp.resize(6, tmp[2]);
					tmp[3] = tmp[2] = tmp[1];
					tmp[1] = tmp[0];
				}

				if (tmp.size() == 6) {
					// We append the alpha value.
					tmp.append("ff");
					
					// We convert it to an int.
					uint32_t rgba;
					
					if (StringHelper::fromString(tmp, rgba, std::hex)) {
						setRGBA(rgba);
					}
				}

			} else if (tmp[0] == 'r') {
				// It's either for the color "red", rgb or rgba.
				if (tmp == std::string("red")) {
					operator=(RED);

				} else {
					// We check if the color is in rgba format.
					bool rgba = tmp.size() >= 13 &&
					            (tmp.substr(0, 5) == std::string("rgba(")) &&
					            *tmp.rbegin() == ')';

					if (rgba) {
						tmp.erase(0, 5);
						tmp.erase(tmp.size() - 1, 1);

					} else if (tmp.size() >= 10 &&
					           tmp.substr(0, 4) == std::string("rgb(") &&
					           *tmp.rbegin() == ')') {
						tmp.erase(0, 4);
						tmp.erase(tmp.size() - 1, 1);
					}

					std::vector<std::string> componentList;
					componentList.reserve(4);
					StringHelper::tokenize(tmp, componentList, ",");

					if ((rgba && componentList.size() == 4) ||
					    (!rgba && componentList.size() == 3)) {
						// We re-use the rgba variable.
						rgba = true;
						// We check if the rgb components use percentages.
						int r, g, b, a;

						// We make sure the rgb components are not empty.
						if (!componentList[0].empty() &&
						    !componentList[1].empty() &&
						    !componentList[2].empty()) {
							if (*componentList[0].rbegin() == '%' &&
							    *componentList[1].rbegin() == '%' &&
							    *componentList[2].rbegin() == '%') {
								// We remove the percentage signs.
								componentList[0].erase(componentList[0].size() - 1, 1);
								componentList[1].erase(componentList[1].size() - 1, 1);
								componentList[2].erase(componentList[2].size() - 1, 1);

								// We convert the percentages to floats.
								float fr, fg, fb;

								if (StringHelper::fromString(componentList[0], fr) &&
								    StringHelper::fromString(componentList[1], fg) &&
								    StringHelper::fromString(componentList[2], fb)) {
									r = static_cast<int>(fr * 2.55f);
									g = static_cast<int>(fg * 2.55f);
									b = static_cast<int>(fb * 2.55f);

								} else {
									rgba = false;
								}

							} else if (*componentList[0].rbegin() != '%' &&
							           *componentList[1].rbegin() != '%' &&
							           *componentList[2].rbegin() != '%') {
								// We read the rgb values.
								if (!(StringHelper::fromString(componentList[0], r) &&
								      StringHelper::fromString(componentList[1], g) &&
								      StringHelper::fromString(componentList[2], b))) {
									rgba = false;
								}

							} else {
								rgba = false;
							}

						} else {
							rgba = false;
						}

						// If the rgb components were valid.
						if (rgba) {
							if (componentList.size() == 4) {
								// We make sure the alpha value is not empty.
								if (!componentList[3].empty()) {
									// We check if the alpha value is in percentage.
									if (*componentList[3].rbegin() == '%') {
										// We remove the percentage sign.
										componentList[3].erase(componentList[3].size() - 1, 1);
										// We convert the percentage.
										float fa;

										if (StringHelper::fromString(componentList[3], fa)) {
											a = static_cast<int>(fa * 2.55f);

										} else {
											rgba = false;
										}

									} else {
										float fa;

										if (StringHelper::fromString(componentList[3], fa)) {
											a = static_cast<int>(fa * 255.0f);

										} else {
											rgba = false;
										}
									}

								} else {
									rgba = false;
								}

							} else {
								a = 255;
							}
						}

						if (rgba) {
							setRGBA(r, g, b, a);
						}
					}
				}

			} else {
				// It's either for a color keyword or invalid.
				std::map<std::string, Color>::const_iterator colorFound = cssColorMap.find(tmp);

				if (colorFound != cssColorMap.end()) {
					operator=(colorFound->second);
				}
			}
		}
	}

	std::map<std::string, Color> createCssColorMap() {
		std::map<std::string, Color> result;
		result.insert(std::make_pair(std::string("black"), Color::BLACK));
		result.insert(std::make_pair(std::string("silver"), Color::SILVER));
		result.insert(std::make_pair(std::string("gray"), Color::GRAY));
		result.insert(std::make_pair(std::string("white"), Color::WHITE));
		result.insert(std::make_pair(std::string("maroon"), Color::MAROON));
		result.insert(std::make_pair(std::string("purple"), Color::PURPLE));
		result.insert(std::make_pair(std::string("fuchsia"), Color::FUCHSIA));
		result.insert(std::make_pair(std::string("green"), Color::GREEN));
		result.insert(std::make_pair(std::string("lime"), Color::LIME));
		result.insert(std::make_pair(std::string("olive"), Color::OLIVE));
		result.insert(std::make_pair(std::string("yellow"), Color::YELLOW));
		result.insert(std::make_pair(std::string("navy"), Color::NAVY));
		result.insert(std::make_pair(std::string("blue"), Color::BLUE));
		result.insert(std::make_pair(std::string("teal"), Color::TEAL));
		result.insert(std::make_pair(std::string("aqua"), Color::AQUA));
		result.insert(std::make_pair(std::string("transparent"), Color::TRANSPARENT));
		return result;
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

	void Color::serialize(Value &node, bool setName) const {
		if (setName) {
			node.setName("Color");
		}

		// We set the value's attributes.
		node["red"].setInt(getRed());
		node["red"].setAttribute(true);
		node["green"].setInt(getGreen());
		node["green"].setAttribute(true);
		node["blue"].setInt(getBlue());
		node["blue"].setAttribute(true);
		node["alpha"].setInt(getAlpha());
		node["alpha"].setAttribute(true);
	}

	bool Color::deserialize(const Value &node) {
		bool result = true;
		Object::const_iterator itRed = node.getObject().find("red");
		Object::const_iterator itGreen = node.getObject().find("green");
		Object::const_iterator itBlue = node.getObject().find("blue");
		Object::const_iterator itAlpha = node.getObject().find("alpha");

		if (itRed != node.getObject().end() &&
		    itGreen != node.getObject().end() &&
		    itBlue != node.getObject().end() &&
		    itAlpha != node.getObject().end() &&
		    itRed->second.isNumeric() &&
		    itGreen->second.isNumeric() &&
		    itBlue->second.isNumeric() &&
		    itAlpha->second.isNumeric()) {

			setRGBA(itRed->second.getInt(), itGreen->second.getInt(),
			        itBlue->second.getInt(), itAlpha->second.getInt());

		} else {
			result = false;
		}

		return result;
	}

	bool Color::isValidValue(const Value &node) {
		Object::const_iterator itRed = node.getObject().find("red");
		Object::const_iterator itGreen = node.getObject().find("green");
		Object::const_iterator itBlue = node.getObject().find("blue");
		Object::const_iterator itAlpha = node.getObject().find("alpha");
		return itRed != node.getObject().end() &&
		       itGreen != node.getObject().end() &&
		       itBlue != node.getObject().end() &&
		       itAlpha != node.getObject().end() &&
		       itRed->second.isNumeric() &&
		       itGreen->second.isNumeric() &&
		       itBlue->second.isNumeric() &&
		       itAlpha->second.isNumeric();
	}

	std::ostream &operator<<(std::ostream &output, const Color &color) {
		Value tmpValue;
		DefaultSerializer::serialize(color, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}

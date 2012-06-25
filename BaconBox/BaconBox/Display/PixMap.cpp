#include "PixMap.h"

#include <algorithm>

#include "Console.h"
#include "Color.h"

namespace BaconBox {
	PixMap::PixMap() : width(0), height(0),
		colorFormat(ColorFormat::RGBA), buffer(NULL) {
	}

	PixMap::PixMap(const PixMap &src) : width(src.width),
		height(src.height), colorFormat(src.colorFormat), buffer(NULL) {
		if (src.buffer) {
			unsigned int bufferSize = width * height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1));
			buffer = new uint8_t[bufferSize];

			for (unsigned int i = 0; i < bufferSize; ++i) {
				buffer[i] = src.buffer[i];
			}
		}
	}

	PixMap::PixMap(unsigned int newWidth, unsigned int newHeight,
	               ColorFormat newColorFormat) : width(newWidth),
		height(newHeight), colorFormat(newColorFormat),
		buffer(new uint8_t[width *height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1))]) {
	}

	PixMap::PixMap(unsigned int newWidth, unsigned int newHeight,
	               uint8_t defaultValue, ColorFormat newColorFormat) :
		width(newWidth), height(newHeight), colorFormat(newColorFormat),
		buffer(new uint8_t[width *height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1))]) {
		unsigned int tmpLength = width * height * ((colorFormat == ColorFormat::RGBA) ? (4) : (1));

		for (unsigned int i = 0; i < tmpLength; ++i) {
			buffer[i] = defaultValue;
		}
	}

	PixMap::PixMap(uint8_t *newBuffer, unsigned int newWidth,
	               unsigned int newHeight, ColorFormat newColorFormat) :
		width(newWidth), height(newHeight), colorFormat(newColorFormat),
		buffer(newBuffer) {
	}

	PixMap::~PixMap() {
		if (buffer) {
			delete [] buffer;
		}
	}

	PixMap &PixMap::operator=(const PixMap &src) {
		if (this != &src) {
			if (buffer) {
				delete [] buffer;
			}

			width = src.width;
			height = src.height;
			colorFormat = src.colorFormat;

			if (src.buffer) {
				unsigned int bufferSize = width * height * ((colorFormat == ColorFormat::RGBA) ? (16) : (1));
				buffer = new uint8_t[bufferSize];

				for (unsigned int i = 0; i < bufferSize; ++i) {
					buffer[i] = src.buffer[i];
				}
			}
		}

		return *this;
	}

	void PixMap::convertTo(ColorFormat format) {
		uint8_t *tempBuffer;
		int pixelCount = width * height;
		bool successful = false;

		if (this->colorFormat == ColorFormat::RGBA && format == ColorFormat::ALPHA) {
			tempBuffer = new uint8_t[pixelCount];

			for (int i = 0; i < pixelCount; i++) {
				tempBuffer[i] = buffer[i * 4];
			}

			colorFormat = ColorFormat::ALPHA;
			successful = true;

		} else if (this->colorFormat == ColorFormat::ALPHA && format == ColorFormat::RGBA) {
			tempBuffer = new uint8_t[pixelCount * 4];

			for (int i = 0; i < pixelCount; i++) {
				for (int j = 0; j < 3; j++) {
					tempBuffer[i * 4 + j] = buffer[i];
				}

				tempBuffer[i * 4 + 3] = 255;
			}

			colorFormat = ColorFormat::RGBA;
			successful = true;

		}

		if (successful) {
			delete buffer;
			buffer = tempBuffer;
		}
	}

	void PixMap::makeColorTransparent(const Color &transparentColor) {
		// We make sure the pix map has the right color format.
		if (buffer && colorFormat == ColorFormat::RGBA) {
			unsigned int i = 0;
			unsigned int j;
			size_t index = 0;

			// For each texel.
			while (i < width) {
				j = 0;

				while (j < height) {
					// We check if the color is to be transparent.
					if (std::equal(&buffer[index], &buffer[index] + 3, transparentColor.getComponents())) {
						// We make it completely transparent.
						std::fill(&buffer[index], &buffer[index] + 4, uint8_t(0));
					}

					index += 4;
					++j;
				}

				++i;
			}
		}
	}

	unsigned int PixMap::getWidth() const {
		return width;
	}

	unsigned int PixMap::getHeight() const {
		return height;
	}

	ColorFormat PixMap::getColorFormat() const {
		return colorFormat;
	}

	uint8_t *PixMap::getBuffer() {
		return buffer;
	}

	const uint8_t *PixMap::getBuffer() const {
		return buffer;
	}

	void PixMap::insertSubPixMap(const PixMap &subPixMap, unsigned int xOffset,
	                             unsigned int yOffset) {
		if (subPixMap.getColorFormat() == colorFormat) {
			insertSubPixMap(subPixMap.getBuffer(), subPixMap.getWidth(), subPixMap.getHeight(), xOffset, yOffset);

		} else {
			Console::println("Can't insert sub pixmap into current pixmap, because the color format isn't compatible.");
		}
	}


	void PixMap::insertSubPixMap(const uint8_t *subBuffer, unsigned int subWidth,
	                             unsigned int subHeight, unsigned int xOffset,
	                             unsigned int yOffset) {
		if (subWidth > 0u && subHeight > 0u) {
			unsigned int currentWidth = width;
			unsigned int currentHeight = height;

			unsigned int maxX = std::min(subWidth - 1u + xOffset, currentWidth);
			unsigned int maxY = std::min(subHeight - 1u  + yOffset, currentHeight);

			if (maxX > xOffset && maxY > yOffset) {
				unsigned int pixelByteCount;

				if (colorFormat == ColorFormat::RGBA) {
					pixelByteCount = 4;

				} else if (colorFormat == ColorFormat::ALPHA) {
					pixelByteCount = 1;
				}

				for (unsigned int i = yOffset; i <= maxY; ++i) {
					for (unsigned int j = xOffset; j <= maxX; ++j) {
						for (unsigned int k = 0; k < pixelByteCount; ++k) {
							buffer[(i * currentWidth + j) * pixelByteCount + k] =
							    subBuffer[(subWidth * (i - yOffset) + (j - xOffset)) * pixelByteCount + k];
						}
					}
				}
			}
		}
	}
}

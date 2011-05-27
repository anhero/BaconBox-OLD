#include "PixMap.h"

#include <algorithm>

#include "Console.h"

using namespace RedBox;

PixMap::PixMap() : Object(), width(0), height(0), colorFormat(ColorFormat::RGBA),
	buffer(NULL) {
}

PixMap::PixMap(const PixMap& src) : Object(src), width(src.width),
	height(src.height), colorFormat(src.colorFormat), buffer(NULL) {
	if(src.buffer) {
		unsigned int bufferSize = width * height * ((colorFormat == ColorFormat::RGBA) ? (16) : (1));
		buffer = new uint8_t[bufferSize];

		for(unsigned int i = 0; i < bufferSize; ++i) {
			buffer[i] = src.buffer[i];
		}
	}
}

PixMap::PixMap(unsigned int newWidth, unsigned int newHeight,
			   ColorFormat::Enum newColorFormat) : Object(), width(newWidth),
	height(newHeight), colorFormat(newColorFormat), buffer(NULL) {
	width = newWidth;
	height = newHeight;
	colorFormat = newColorFormat;
	buffer = new uint8_t[width* height * ((colorFormat == ColorFormat::RGBA) ? (16) : (1))];
}

PixMap::PixMap(uint8_t* newBuffer, unsigned int newWidth,
			   unsigned int newHeight, ColorFormat::Enum newColorFormat) :
	Object(), width(newWidth), height(newHeight), colorFormat(newColorFormat),
	buffer(newBuffer) {
}

PixMap::~PixMap() {
	if(buffer) {
		delete [] buffer;
	}
}

PixMap& PixMap::operator=(const PixMap& src) {
	if(this != &src) {
		if(buffer) {
			delete [] buffer;
		}

		width = src.width;
		height = src.height;
		colorFormat = src.colorFormat;

		if(src.buffer) {
			unsigned int bufferSize = width * height * ((colorFormat == ColorFormat::RGBA) ? (16) : (1));
			buffer = new uint8_t[bufferSize];

			for(unsigned int i = 0; i < bufferSize; ++i) {
				buffer[i] = src.buffer[i];
			}
		}
	}
}


unsigned int PixMap::getWidth() const {
	return width;
}

unsigned int PixMap::getHeight() const {
	return height;
}

ColorFormat::Enum PixMap::getColorFormat() const {
	return colorFormat;
}

uint8_t* PixMap::getBuffer() {
	return buffer;
}

void PixMap::insertSubPixMap(PixMap* subPixMap, unsigned int xOffset,
                             unsigned int yOffset) {
	if(subPixMap->getColorFormat() == colorFormat) {
		insertSubPixMap(subPixMap->getBuffer(), subPixMap->getWidth(), subPixMap->getHeight(), xOffset, yOffset);
	} else {
		Console::print("Can't insert sub pixmap into current pixmap, because the color format isn't compatible.");
	}
}


void PixMap::insertSubPixMap(uint8_t* subBuffer, unsigned int subWidth,
                             unsigned int subHeight, unsigned int xOffset,
                             unsigned int yOffset) {
	if(subWidth > 0u && subHeight > 0u) {
		unsigned int pixelByteCount;

		unsigned int currentWidth = width;
		unsigned int currentHeight = height;

		unsigned int maxX = std::min(subWidth - 1u + xOffset, currentWidth);
		unsigned int maxY = std::min(subHeight - 1u  + yOffset, currentHeight);

		unsigned int baseX = std::max(xOffset, 0u);
		unsigned int baseY = std::max(yOffset, 0u);

		if(maxX > baseX && maxY > baseX) {

			if(colorFormat == ColorFormat::RGBA) {
				pixelByteCount = 4;
			} else if(colorFormat == ColorFormat::ALPHA) {
				pixelByteCount = 1;
			}

			for(unsigned int i = baseY; i <= maxY; ++i) {
				for(unsigned int j = baseX; j <= maxX; ++j) {
					for(unsigned int k = 0; k < pixelByteCount; ++k) {
						buffer[(currentWidth * (i - yOffset) + (j - xOffset)) * pixelByteCount + k] =
						    subBuffer[(subWidth * i + j) * pixelByteCount + k];
					}
				}
			}
		}
	}
}

#include "GraphicString.h"

#include <cmath>
#include <algorithm>

#include "TextureInfo.h"
#include "Console.h"
#include "UTFConvert.h"
#include "Font.h"
#include "DeleteHelper.h"

using namespace RedBox;

GraphicString::GraphicString(Font* newFont, const Vec2& newPosition,
							 TextAlignment newAlignment,
							 TextDirection newDirection) :
	GraphicBody(newPosition), font(newFont), color(Color::BLACK),
	 needReset(false), alignment(newAlignment), direction(newDirection),
	widthCache(0.0f) {
	setString();
}

GraphicString::GraphicString(Font* newFont, float newXPosition,
							 float newYPosition, TextAlignment newAlignment,
							 TextDirection newDirection) :
	GraphicBody(Vec2(newXPosition, newYPosition)), font(newFont),
	color(Color::BLACK), needReset(false), alignment(newAlignment),
	direction(newDirection), widthCache(0.0f) {
	setString();
}

Font* GraphicString::getFont() {
	return font;
}

void GraphicString::setFont(Font* newFont) {
	font = newFont;
	setText(internalString);
}

const Color& GraphicString::getColor() const {
	return color;
}

void GraphicString::setColor(const Color& newColor) {
	color = newColor;
	setColor();
}

TextAlignment GraphicString::getAlignment() const {
	return alignment;
}

void GraphicString::setAlignment(TextAlignment newAlignment) {
	alignment = newAlignment;
	setPosition();
}

TextDirection GraphicString::getDirection() const {
	return direction;
}

void GraphicString::setDirection(TextDirection newDirection) {
	direction = newDirection;
	setPosition();
}

void GraphicString::setText(const std::string& text) {
	setText(UTFConvert::decodeUTF8(text));
}

void GraphicString::setText(const RB_String32& text) {
	internalString = text;

	if(font) {
		flushCharacters();

		for(RB_String32::const_iterator i = text.begin(); i != text.end(); i++) {
			Glyph* aGlyph = font->getGlyph(*i);
			TextureInfo* glyphTextureInfo = aGlyph->textureInfo;
			Sprite* aSprite = NULL;

			if(aGlyph->size.getX() != 0) {
				aSprite = new Sprite(glyphTextureInfo, aGlyph->size.getX(), aGlyph->size.getY());
			}

			characters.push_back(std::pair<Glyph*, Sprite*>(aGlyph, aSprite));
		}

		setString();
	} else {
		Console::print("Trying to set text to a GraphicString without any font set.");
		Console::printTrace();
	}
}

void GraphicString::setPosition(float newXPosition, float newYPosition) {
	GraphicBody::setPosition(newXPosition, newYPosition);
	needReset = true;
}

void GraphicString::setXPosition(float newXPosition) {
	this->GraphicBody::setXPosition(newXPosition);
	needReset = true;
}

void GraphicString::setYPosition(float newYPosition) {
	this->GraphicBody::setYPosition(newYPosition);
	needReset = true;
}

void GraphicString::setPixelSize(int pixelSize) {
	font->setPixelSize(pixelSize);
	setText(internalString);
}

void GraphicString::setPointSize(int pointSize, int dpi) {
	font->setPointSize(pointSize, dpi);
	setText(internalString);
}

void GraphicString::setAutomaticLineHeight() {
	font->setAutomaticLineHeight();
	setPosition();
}

void GraphicString::setManualLineHeight(int lineHeight) {
	font->setManualLineHeight(lineHeight);
	setPosition();
}

void GraphicString::update() {
	for(std::list<std::pair<Glyph*, Sprite*> >::iterator i = characters.begin();
		i != characters.end(); i++) {
		// We need to check for null pointer since space does not have sprite.
		if(i->second != NULL) {
			i->second->update();
		}
	}
}

void GraphicString::render() {
	if(needReset) {
		setString();
	}

	for(GlyphList::iterator i = characters.begin(); i != characters.end();
		++i) {
		// We need to check for null pointer since space does not have sprite.
		if(i->second != NULL) {
			i->second->render();
		}
	}
}

float RedBox::GraphicString::getWidth() const {
	return widthCache;
}

float RedBox::GraphicString::getHeight() const {
	if(font) {
		return font->getLineHeight();
	} else {
		return 0.0f;
	}
}

void GraphicString::setString() {
	setColor();
	setPosition();
	needReset = false;
}

void GraphicString::setPosition() {
	if(font) {
		int lineHeight = font->getLineHeight();
		float x = floorf(this->GraphicBody::getXPosition());
		float y = floorf(this->GraphicBody::getYPosition());
		//float x = this->GraphicBody::getXPosition();
		//float y = this->GraphicBody::getYPosition();

		//We check if the direction is horizontal (alignment adjustement are different for
		//vertical direction.
		if(direction == TextDirection::LEFT_TO_RIGHT || direction == TextDirection::RIGHT_TO_LEFT) {
			//If the direction is left to right we iterate to set the position (we pretend it's left align first, since we need
			// to get the ending position to calculate the adjustment factor.
			if(direction == TextDirection::LEFT_TO_RIGHT) {
				for(GlyphList::iterator i = characters.begin();
					i != characters.end(); ++i) {
					//We need to check for null pointer since space does not have sprite
					if(i->second != NULL) {
						i->second->setPosition(x + i->first->horizontalBearing.getX(), y + lineHeight + (i->first->size.getY() - i->first->horizontalBearing.getY()) - i->first->size.getY());
					}

					x += i->first->advance.getX();
				}
			}
			//If the direction is right to left we iterate to set the position (we pretend it's left align first, since we need
			// to get the ending position to calculate the adjustment factor.
			else if(direction == TextDirection::RIGHT_TO_LEFT) {
				for(GlyphList::iterator i = characters.begin();
					i != characters.end(); ++i) {
					//We need to check for null pointer since space does not have sprite
					if(i->second != NULL) {
						i->second->setPosition(x + i->first->horizontalBearing.getX(), y + lineHeight + (i->first->size.getY() - i->first->horizontalBearing.getY()) - i->first->size.getY());
					}

					x += i->first->advance.getX();
				}
			}

			float xAdjustment = (alignment == TextAlignment::LEFT) ? (0.0f) : ((alignment == TextAlignment::RIGHT) ? (this->GraphicBody::getXPosition() - x) : ((this->GraphicBody::getXPosition() - x) * 0.5f));

			for(GlyphList::iterator i = characters.begin();
				i != characters.end(); ++i) {
				//We need to check for null pointer since space does not have sprite
				if(i->second != NULL) {
					i->second->moveX(xAdjustment);
				}
			}

			if(characters.size() > 0) {
				// We add the last glyph's width to the position...
				x += (--characters.end())->first->advance.getX();
			}
		}

		// To then put it in the cache.
		widthCache = x;
	}
}

void GraphicString::setColor() {
	for(GlyphList::iterator i = characters.begin();
		i != characters.end(); ++i) {
		// We do not delete the glyph, it would break the glyph cache.
		// Also we must check for null pointer, since space does not have sprite
		if(i->second) {
			i->second->setMainColor(color);
		}
	}

}

void GraphicString::flushCharacters() {
	std::for_each(characters.begin(), characters.end(), DeletePointerFromPair());
	characters.clear();
}


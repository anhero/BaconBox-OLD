#include "GraphicString.h"
#include "TextureInfo.h"
#include "Console.h"
#include "UTFConvert.h"
#include "Font.h"

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
	needReset = true;
}

TextAlignment GraphicString::getAlignment() const {
	return alignment;
}

void GraphicString::setAlignment(TextAlignment newAlignment) {
	alignment = newAlignment;
	needReset = true;
}

TextDirection GraphicString::getDirection() const {
	return direction;
}

void GraphicString::setDirection(TextDirection newDirection) {
	direction = newDirection;
	needReset = true;
}

void GraphicString::setText(const std::string& text) {
	setText(UTFConvert::decodeUTF8(text));
}

void GraphicString::setText(const RB_String32& text) {
	internalString = text;

	if(font != NULL) {
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

		needReset = true;
	} else {
		Console::print("Trying to set text with no font loaded.");
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
	needReset = true;
}

void GraphicString::setManualLineHeight(int lineHeight) {
	font->setManualLineHeight(lineHeight);
	needReset = true;
}

void GraphicString::update() {
	for(std::list<std::pair<Glyph*, Sprite*> >::iterator i = characters.begin();
		i != characters.end(); i++) {
		//We need to check for null pointer since space does not have sprite
		if(i->second != NULL) {
			i->second->update();
		}
	}
}

void GraphicString::render() {
	if(needReset) {
		setString();
	}

	for(std::list<std::pair<Glyph*, Sprite*> >::iterator i = characters.begin();
		i != characters.end(); i++) {
		// We need to check for null pointer since space does not have sprite.
		if(i->second != NULL) {
			i->second->render();
		}
	}
}

float RedBox::GraphicString::getWidth() const {
	return this->widthCache;
}

float RedBox::GraphicString::getHeight() const {
	return this->font->getLineHeight();
}

void GraphicString::setString() {
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
	std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();

	for(i = begin; i != end; i++) {
		//We do not delete the glyph, it would break the glyph cache.
		//Also we must check for null pointer, since space does not have sprite
		if(i->second != NULL) {
			i->second->setMainColor(color);
		}
	}

	setPosition();
	needReset = false;
}

void GraphicString::flushCharacters() {
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
	std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();

	for(i = begin; i != end; i++) {
		//We do not delete the glyph, it would break the glyph cache.
		//Also we must check for null pointer, since space does not have sprite
		if(i->second != NULL) {
			delete i->second;
		}
	}

	characters.clear();
}

void GraphicString::setPosition() {
	if(font) {
		int lineHeight = font->getLineHeight();
		float x = this->GraphicBody::getXPosition();
		float y = this->GraphicBody::getYPosition();

		//We check if the direction is horizontal (alignment adjustement are different for
		//vertical direction.
		if(direction == TextDirection::LEFT_TO_RIGHT || direction == TextDirection::RIGHT_TO_LEFT) {
			//If the direction is left to right we iterate to set the position (we pretend it's left align first, since we need
			// to get the ending position to calculate the adjustment factor.
			if(direction == TextDirection::LEFT_TO_RIGHT) {
				std::list<std::pair<Glyph*, Sprite*> >::iterator i;
				std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
				std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();

				for(i = begin; i != end; i++) {
					//We need to check for null pointer since space does not have sprite
					if(i->second != NULL) {
						i->second->setPosition(x + i->first->horizontalBearing.getX(), y + lineHeight + (i->first->size.getY() - i->first->horizontalBearing.getY()) - i->first->size.getY());
					}

					x += static_cast<float>(i->first->advance.getX());
				}
			}
			//If the direction is right to left we iterate to set the position (we pretend it's left align first, since we need
			// to get the ending position to calculate the adjustment factor.
			else if(direction == TextDirection::RIGHT_TO_LEFT) {
				std::list<std::pair<Glyph*, Sprite*> >::reverse_iterator i;
				std::list<std::pair<Glyph*, Sprite*> >::reverse_iterator begin = characters.rbegin();
				std::list<std::pair<Glyph*, Sprite*> >::reverse_iterator end = characters.rend();

				for(i = begin; i != end; i++) {
					//We need to check for null pointer since space does not have sprite
					if(i->second != NULL) {
						i->second->setPosition(x + i->first->horizontalBearing.getX(), y + lineHeight + (i->first->size.getY() - i->first->horizontalBearing.getY()) - i->first->size.getY());
					}

					x += static_cast<float>(i->first->advance.getX());
				}
			}

			float xAdjustment = (alignment == TextAlignment::LEFT) ? (0.0f) : ((alignment == TextAlignment::RIGHT) ? (this->GraphicBody::getXPosition() - x) : ((this->GraphicBody::getXPosition() - x) * 0.5f));

			for(std::list<std::pair<Glyph*, Sprite*> >::iterator i = characters.begin(); i != characters.end(); i++) {
				//We need to check for null pointer since space does not have sprite
				if(i->second != NULL) {
					i->second->moveX(xAdjustment);
				}
			}

			if(characters.size() > 0) {
				// We add the last glyph's width to the position...
				x += static_cast<float>((--characters.end())->first->advance.getX());
			}
		}

		// To then put it in the cache.
		widthCache = x;
	}
}

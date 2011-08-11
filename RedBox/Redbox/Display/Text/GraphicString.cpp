#include "GraphicString.h"

#include <cmath>
#include <algorithm>

#include "TextureInfo.h"
#include "Console.h"
#include "UTFConvert.h"
#include "Font.h"
#include "DeleteHelper.h"

using namespace RedBox;

GraphicString::GraphicString(Font* newFont, TextAlignment newAlignment,
                             TextDirection newDirection) :
	GraphicBody(), font(newFont), color(Color::BLACK), alignment(newAlignment),
	direction(newDirection) {
}

Font* GraphicString::getFont() {
	return font;
}

void GraphicString::setFont(Font* newFont) {
	font = newFont;
	setText(text);
}

const Color& GraphicString::getColor() const {
	return color;
}

void GraphicString::setColor(const Color& newColor) {
	color = newColor;

	for(GlyphList::iterator i = characters.begin(); i != characters.end();
	    ++i) {
		if(i->second) {
			i->second->setMainColor(newColor);
		}
	}
}

TextAlignment GraphicString::getAlignment() const {
	return alignment;
}

void GraphicString::setAlignment(TextAlignment newAlignment) {
	alignment = newAlignment;
}

TextDirection GraphicString::getDirection() const {
	return direction;
}

void GraphicString::setDirection(TextDirection newDirection) {
	direction = newDirection;
}

std::string GraphicString::getText() const {
	return UTFConvert::encodeToUTF8(text);
}

const String32& GraphicString::getTextUtf32() const {
	return text;
}

void GraphicString::setText(const std::string& newText) {
	setText(UTFConvert::decodeUTF8(newText));
}

void GraphicString::setText(const String32& newText) {
	text = newText;

	clearCharacters();

	if(font) {

		float tmpAngle = getAngle(), tmpWidth = getWidth();
		this->GraphicBody::setAngle(0.0f);

		Glyph* tmpGlyph = NULL;
		Sprite* tmpSprite = NULL;

		for(String32::const_iterator i = text.begin(); i != text.end();
		    ++i) {
			tmpGlyph = font->getGlyph(*i);

			if(tmpGlyph->size.getX() > 0.0f) {
				tmpSprite = new Sprite(tmpGlyph->textureInfo, tmpGlyph->size.getX(), tmpGlyph->size.getY());
				tmpSprite->setScaling(getScaling());
				tmpSprite->setMainColor(color);
			} else {
				tmpSprite = NULL;
			}

			characters.push_back(GlyphList::value_type(tmpGlyph, tmpSprite));
		}

		if(alignment == TextAlignment::LEFT ||
		   alignment == TextAlignment::RIGHT ||
		   alignment == TextAlignment::CENTER) {
			float lineHeight = static_cast<float>(font->getLineHeight());

			// We check if the direction is horizontal (alignment adjustements
			// are different for vertical direction.
			if(direction == TextDirection::LEFT_TO_RIGHT ||
			   direction == TextDirection::RIGHT_TO_LEFT) {
				float tmpX = 0.0f, minX, maxX, minY, maxY;
				bool started = false;

				for(GlyphList::iterator i = characters.begin();
				    i != characters.end(); ++i) {
					// We need to check for null pointers since spaces do not
					// have sprites.
					if(i->second) {
						i->second->setPosition(tmpX + i->first->horizontalBearing.getX() * getXScaling(),
						                       (lineHeight + (i->first->size.getY() - i->first->horizontalBearing.getY()) - i->first->size.getY()) * getYScaling());

						if(started) {
							if(i->second->getXPosition() < minX) {
								minX = i->second->getXPosition();
							}

							if(i->second->getXPosition() + i->second->getWidth() > maxX) {
								maxX = i->second->getXPosition() + i->second->getWidth();
							}

							if(i->second->getYPosition() < minY) {
								minY = i->second->getYPosition();
							}

							if(i->second->getYPosition() + i->second->getHeight() > maxY) {
								maxY = i->second->getYPosition() + i->second->getHeight();
							}
						} else {
							minX = i->second->getXPosition();
							maxX = minX + i->second->getWidth();
							minY = i->second->getYPosition();
							maxY = minY + i->second->getHeight();
							started = true;
						}
					}

					tmpX += i->first->advance.getX() * getXScaling();
				}

				Vec2 newPosition = getPosition();

				if(alignment == TextAlignment::RIGHT) {
					newPosition += Vec2(tmpWidth, 0.0f) - Vec2(maxX - minX, 0.0f);
				} else if(alignment == TextAlignment::CENTER) {
					Console::print(newPosition);
					newPosition += Vec2(tmpWidth, 0.0f) * 0.5f - Vec2(maxX - minX, 0.0f) * 0.5f;
					Console::print(newPosition);
				}

				Vec2 delta = newPosition - Vec2(minX, minY);

				for(GlyphList::iterator i = characters.begin();
				    i != characters.end(); ++i) {
					if(i->second) {
						i->second->move(delta);
					}
				}

				this->GraphicBody::setPosition(newPosition.getX(), newPosition.getY());
			}
		}

		setAngle(tmpAngle);

	} else {
		Console::print("Trying to set text to a GraphicString without any font set.");
		Console::printTrace();
	}
}

void GraphicString::setPosition(float newXPosition, float newYPosition) {
	Vec2 delta = Vec2(newXPosition, newYPosition) - getPosition();
	this->GraphicBody::setPosition(newXPosition, newYPosition);

	for(GlyphList::iterator i = characters.begin();
	    i != characters.end(); ++i) {
		if(i->second) {
			i->second->move(delta);
		}
	}
}

void GraphicString::setScaling(float newXScaling, float newYScaling) {
	this->GraphicBody::setScaling(newXScaling, newYScaling);
	Vec2 center = getPosition() + Vec2(getWidth(), getHeight()) * 0.5f;
	setText(text);
	setPosition(center - Vec2(getWidth(), getHeight()) * 0.5f);
}

void GraphicString::setAngle(float newAngle) {
	float oldAngle = getAngle();
	this->GraphicBody::setAngle(newAngle);
	Vec2 center = Vec2(getXPosition() + getWidth() * 0.5f,
	                   getYPosition() + getHeight() * 0.5f);

	for(GlyphList::iterator i = characters.begin();
	    i != characters.end(); ++i) {
		if(i->second) {
			i->second->rotateFromPoint(newAngle - oldAngle, center);
		}
	}

	if(!characters.empty()) {
		bool started = false;
		float minX, minY;

		for(GlyphList::iterator i = characters.begin();
		    i != characters.end(); ++i) {
			if(i->second) {
				if(started) {
					if(i->second->getXPosition() < minX) {
						minX = i->second->getXPosition();
					}

					if(i->second->getYPosition() < minY) {
						minY = i->second->getYPosition();
					}
				} else {
					minX = i->second->getXPosition();
					minY = i->second->getYPosition();
					started = true;
				}
			}
		}

		if(started) {
			this->GraphicBody::setPosition(minX, minY);
		}
	}
}

void GraphicString::setPixelSize(int pixelSize) {
	if(font) {
		font->setPixelSize(pixelSize);
		setText(text);
	}
}

void GraphicString::setPointSize(int pointSize, int dpi) {
	if(font) {
		font->setPointSize(pointSize, dpi);
		setText(text);
	}
}

void GraphicString::setAutomaticLineHeight() {
	if(font) {
		font->setAutomaticLineHeight();
	}
}

void GraphicString::setManualLineHeight(int lineHeight) {
	if(font) {
		font->setManualLineHeight(lineHeight);
	}
}

void GraphicString::update() {
	for(std::list<std::pair<Glyph*, Sprite*> >::iterator i = characters.begin();
	    i != characters.end(); ++i) {
		// We need to check for null pointer since space does not have sprite.
		if(i->second) {
			i->second->update();
		}
	}
}

void GraphicString::render() {
	for(GlyphList::iterator i = characters.begin(); i != characters.end();
	    ++i) {
		// We need to check for null pointer since space does not have sprite.
		if(i->second) {
			i->second->render();
		}
	}
}

float RedBox::GraphicString::getWidth() const {
	if(characters.empty()) {
		return 0.0f;
	} else {
		bool started = false;
		float minX, maxX;

		// We get the lowest and highest horizontal positions.
		for(GlyphList::const_iterator i = characters.begin();
		    i != characters.end(); ++i) {
			if(i->second) {
				if(started) {
					if(i->second->getXPosition() < minX) {
						minX = i->second->getXPosition();
					}

					if(i->second->getXPosition() + i->second->getWidth() > maxX) {
						maxX = i->second->getXPosition() + i->second->getWidth();
					}
				} else {
					minX = i->second->getXPosition();
					maxX = minX + i->second->getWidth();
					started = true;
				}
			}
		}

		// We make sure there was at least one glyph with a sprite.
		if(started) {
			return maxX - minX;
		} else {
			// If there were only glyphs without a sprite (for example: only
			// spaces), we return a width of zero.
			return 0.0f;
		}
	}
}

float RedBox::GraphicString::getHeight() const {
	if(characters.empty()) {
		return 0.0f;
	} else {
		bool started = false;
		float minY, maxY;

		// We get the lowest and highest horizontal positions.
		for(GlyphList::const_iterator i = characters.begin();
		    i != characters.end(); ++i) {
			if(i->second) {
				if(started) {
					if(i->second->getYPosition() < minY) {
						minY = i->second->getYPosition();
					}

					if(i->second->getYPosition() + i->second->getHeight() > maxY) {
						maxY = i->second->getYPosition() + i->second->getHeight();
					}
				} else {
					minY = i->second->getYPosition();
					maxY = minY + i->second->getHeight();
					started = true;
				}
			}
		}

		// We make sure there was at least one glyph with a sprite.
		if(started) {
			return maxY - minY;
		} else {
			// If there were only glyphs without a sprite (for example: only
			// spaces), we return a width of zero.
			return 0.0f;
		}
	}
}

int GraphicString::getLineHeight() const {
	if(font) {
		return font->getLineHeight();
	} else {
		return 0;
	}
}

GraphicBody* GraphicString::clone() const {
	return new GraphicString(*this);
}

void GraphicString::clearCharacters() {
	std::for_each(characters.begin(), characters.end(), DeletePointerFromPair());
	characters.clear();
}


#include "GraphicString.h"
#include "TextureInfo.h"
#include "Debug.h"
#include "UTFConvert.h"

using namespace RedBox;

GraphicString::GraphicString(Font * font, int x, int y, Alignment alignment, StringDirection direction):Renderable(), font(font), x(x), y(y), alignment(alignment), direction(direction){
	color[0] = color[1] = color [2] = color[3]  = 0xFF;
	needReset = false;
};

void GraphicString::setText(const RB_String32 & text){
	internalString = text;
	if(font != NULL){
		flushCharacters();
		RB_String32::const_iterator i;;
		for(i = text.begin(); i != text.end(); i++){
			Glyph * aGlyph = font->getGlyph(*i);
			TextureInfo *  glyphTextureInfo = aGlyph->getTextureInfo();
			Sprite * aSprite = NULL;
			if(aGlyph->getWidth() !=0){
				aSprite = new Sprite(glyphTextureInfo, aGlyph->getWidth(), aGlyph->getHeight());
			}
			characters.push_back(std::pair<Glyph*, Sprite*>(aGlyph, aSprite));
		}
		needReset = true;
	}
	else{
		$ECHO("Trying to set text with no font loaded.");
	}
}

void GraphicString::setText(const std::string & text){
	RB_String32 textUTF32 = UTFConvert::decodeUTF8(text);
	setText(textUTF32);
}

void GraphicString::setPosition(int x, int y){
	//We set the position atribute
	this->x = x;
	this->y = y;
	needReset = true;
	
}
void GraphicString::setPosition(){
	
	int lineHeight = font->getLineHeight();
	int x = this->x;
	int y = this->y;
	//We check if the direction is horizontal (alignment adjustement are different for 
	//vertical direction.
	if(direction == leftToRight || direction == rightToLeft){
		//If the direction is left to right we iterate to set the position (we pretend it's left align first, since we need
		// to get the ending position to calculate the adjustment factor.
		if(direction == leftToRight){
			std::list<std::pair<Glyph*, Sprite*> >::iterator i;
			std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
			std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();
			for(i = begin; i != end; i++){
				//We need to check for null pointer since space does not have sprite
				if (i->second != NULL){
					i->second->setPosition(x+i->first->getHoriBearingX(), y-i->first->getHoriBearingY() - i->first->getHeight()+ lineHeight);
				}
				x += i->first->getXAdvance();
			}
		}
		//If the direction is right to left we iterate to set the position (we pretend it's left align first, since we need
		// to get the ending position to calculate the adjustment factor.
		else if(direction == rightToLeft){
			std::list<std::pair<Glyph*, Sprite*> >::reverse_iterator i;
			std::list<std::pair<Glyph*, Sprite*> >::reverse_iterator begin = characters.rbegin();
			std::list<std::pair<Glyph*, Sprite*> >::reverse_iterator end = characters.rend();
			for(i = begin; i != end; i++){
				//We need to check for null pointer since space does not have sprite
				if (i->second != NULL){
					i->second->setPosition(x+i->first->getHoriBearingX(), y-i->first->getHoriBearingY() - i->first->getHeight()+ lineHeight);
				}
				x += i->first->getXAdvance();
			}
		}
		
		int xAdjustment;
		
		if(alignment == left){
			xAdjustment = 0;
			
		}
		else if(alignment == right){
			xAdjustment = this->x - x;
			
		}
		else if(alignment == center){
			xAdjustment = (this->x-x) * 0.5;
		}
		std::list<std::pair<Glyph*, Sprite*> >::iterator i;
		for(i = characters.begin(); i != characters.end(); i++){
			//We need to check for null pointer since space does not have sprite
			if (i->second != NULL){
				i->second->moveX(xAdjustment);
			}
		}
	}
}



void GraphicString::update(){
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	for(i = characters.begin(); i != characters.end(); i++){
		//We need to check for null pointer since space does not have sprite
		if (i->second != NULL){
			i->second->update();
		}
	}
}
void GraphicString::setPointSize(int pointSize, int dpi){
	font->setPointSize(pointSize, dpi);
	setText(internalString);
}
void GraphicString::setPixelSize(int pixelSize){
	font->setPixelSize(pixelSize);
	setText(internalString);
}

void GraphicString::render(){
	if (needReset){
		setString();
	}
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	for(i = characters.begin(); i != characters.end(); i++){
		//We need to check for null pointer since space does not have sprite
		if (i->second != NULL){
			i->second->render();
		}
	}
}

void GraphicString::setFont(Font * font){
	this->font = font;
	setText(internalString);
}

void GraphicString::setDirection(StringDirection direction){
	this->direction = direction;
	needReset = true;
}

void GraphicString::setAlignment(Alignment alignment){
	this->alignment = alignment;
	needReset = true;
}

void GraphicString::flushCharacters(){
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
	std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();
	for(i = begin; i != end; i++){
		//We do not delete the glyph, it would break the glyph cache.
		//Also we must check for null pointer, since space does not have sprite
		if(i->second != NULL){
			delete i->second;
		}
	}
	characters.clear();
}
void GraphicString::setString(){
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
	std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();
	for(i = begin; i != end; i++){
		//We do not delete the glyph, it would break the glyph cache.
		//Also we must check for null pointer, since space does not have sprite
		if(i->second != NULL){
			i->second->setMainColor(color[0], color[1], color[2], color[3]);
		}
	}
	setPosition();
	needReset = false;
}
void GraphicString::setColor(int red, int green, int blue, int alpha){
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
	needReset = true;	
}


void GraphicString::setAutomaticLineHeight(){
	font->setAutomaticLineHeight();
	needReset = true;
}
void GraphicString::setManualLineHeight(int lineHeight){
	font->setManualLineHeight(lineHeight);
	needReset = true;
}
#include "GraphicString.h"
#include "TextureInfo.h"
#include "Debug.h"
#include "UTFConvert.h"

using namespace RedBox;

GraphicString::GraphicString(Font * font, int x, int y, Alignment alignment, StringDirection direction):Renderable(), font(font), x(x), y(y), alignment(alignment), direction(direction){};

void GraphicString::setText(const RB_String32 & text){
	if(font != NULL){
		RB_String32::const_iterator i;;
		for(i = text.begin(); i != text.end(); i++){
			Glyph * aGlyph = font->getGlyph(*i);
			TextureInfo *  glyphTextureInfo = aGlyph->getTextureInfo();
			Sprite * aSprite = new Sprite(glyphTextureInfo, aGlyph->getWidth(), aGlyph->getHeight());
			characters.push_back(std::pair<Glyph*, Sprite*>(aGlyph, aSprite));
		}
		setPosition(x, y);
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
				i->second->setPosition(x+i->first->getHoriBearingX(), y-i->first->getHoriBearingY() - i->first->getHeight());
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
				i->second->setPosition(x+i->first->getHoriBearingX(), y-i->first->getHoriBearingY() - i->first->getHeight());
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
			i->second->moveX(xAdjustment);
		}
	}
}



void GraphicString::update(){
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	for(i = characters.begin(); i != characters.end(); i++){
		i->second->update();
	}
}

void GraphicString::render(){
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	for(i = characters.begin(); i != characters.end(); i++){
		i->second->render();
	}
}

void GraphicString::setFont(Font * font){
	this->font = font;
}



void GraphicString::setAlignment(Alignment alignment){
	this->alignment = alignment;
}


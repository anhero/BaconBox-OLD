#include "GraphicString.h"
#include "TextureInfo.h"
#include "Debug.h"
#include "UTFConvert.h"

using namespace RedBox;

GraphicString::GraphicString(): Renderable(), font(NULL), x(0), y(0){};
GraphicString::GraphicString(Font * font):Renderable(), font(font), x(0), y(0){};

void GraphicString::setText(RB_String32 & text){
	if(font != NULL){
		RB_String32::iterator i;;
		for(i = text.begin(); i != text.end(); i++){
			Glyph * aGlyph = font->getGlyph(*i);
			TextureInfo *  glyphTextureInfo = aGlyph->getTextureInfo();
			Sprite * aSprite = new Sprite(glyphTextureInfo, glyphTextureInfo->imageWidth, glyphTextureInfo->imageHeight);
			characters.push_back(std::pair<Glyph*, Sprite*>(aGlyph, aSprite));
		}
		setPosition(x, y);
	}
	else{
		$ECHO("Trying to set text with no font loaded.");
	}
}

void GraphicString::setText(std::string & text){
	RB_String32 textUTF32 = UTFConvert::decodeUTF8(text);
	setText(textUTF32);
}

void GraphicString::setPosition(int x, int y){
	this->x = x;
	this->y = y;
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	std::list<std::pair<Glyph*, Sprite*> >::iterator begin = characters.begin();
	std::list<std::pair<Glyph*, Sprite*> >::iterator end = characters.end();
	
	
	if(direction == leftToRight || direction == rightToLeft){
		
		int xAdjustment;
		
		if(direction == rightToLeft){
			std::list<std::pair<Glyph*, Sprite*> >::iterator temp = begin;
			begin = end;
			end = begin;
		}
		for(i = begin; i != end; i++){
			i->second->setPosition(x+i->first->getHoriBearingX(), y+i->first->getHoriBearingY());
			x += i->first->getXAdvance();
		}
		
		
		if(alignment == left){
			xAdjustment = 0;
			
		}
		else if(alignment == right){
			xAdjustment = this->x - x;
			
		}
		else if(alignment == center){
			xAdjustment = (this->x-x) * 0.5;
		}
		for(i = characters.begin(); i != characters.end(); i++){
			i->second->moveX(xAdjustment);
		}
	}
	
}

void GraphicString::update(){
	std::list<std::pair<Glyph*, Sprite*> >::iterator i;
	for(i = characters.begin(); i != characters.end(); i++){
	//	i->second->update();
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


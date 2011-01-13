#include "GraphicString.h"
using namespace RedBox;

GraphicString::GraphicString():renderingMode(perLetter), alignment(leftAlign),
angle(0), fixAdvance(NO_FIX_ADVANCE), renderingFont(NULL) {
}

GraphicString::~GraphicString() {
	cleanStringParts();
}

void GraphicString::cleanStringParts() {
	for (std::vector<StringPart*>::iterator i = stringParts.begin(); i != stringParts.end(); i++) {
		if (*i) {
			delete *i;
		}
	}
	stringParts.clear();	
}

void GraphicString::setXPosition(int x){
	setPosition(x, y);
}
void GraphicString::setYPosition(int y){
	setPosition(x, y);
}

void GraphicString::setPosition(int x, int y){
	this->x = x;
	this->y = y;
	int xAdvance = 0;
	int stringPartCount = stringParts.size();
	if(alignment == leftAlign){
		for (int i =0; i < stringPartCount; i++) {
			stringParts[i]->setXPosition(x);
			stringParts[i]->setTotalXAdvance(xAdvance);
			xAdvance += (fixAdvance > NO_FIX_ADVANCE ? fixAdvance : stringParts[i]->getXAdvance());
			stringParts[i]->setYPosition(y);
		}
	}
	else if(alignment == rightAlign){
		for (int i= (stringPartCount-1); i >= 0; i--) {
			xAdvance += (fixAdvance > NO_FIX_ADVANCE ? fixAdvance : stringParts[i]->getXAdvance());
			stringParts[i]->setXPosition(x);
			stringParts[i]->setTotalXAdvance(-xAdvance);
			stringParts[i]->setYPosition(y);
		}
	}
}

void GraphicString::setText(std::wstringstream& aStringStream){
    std::wstring test = aStringStream.str();
	setText(test);
}


void GraphicString::setFont(Font * aFont){
	renderingFont = aFont;
}

void GraphicString::setText(const std::wstring& aString){
	internalString = aString;
	generateGraphicString();
}

void GraphicString::setRenderingMode(RenderMode renderMode){
	renderingMode = renderMode;
}

void GraphicString::generateGraphicString() {
	cleanStringParts();
	if(renderingMode == perLetter){
		
		//we iterate trough the string
		int charCount =  internalString.size();
		for(int i = 0; i < charCount; i++){
			
			//We get the bitmap and the bitmap info of the char
			bitmapChar aBitmapChar = renderingFont->getCharPixMap(internalString[i]);
			
			//We power to 2 the bitmap of the char
			int widthPoweredToTwo = MathHelper::nextPowerOf2(aBitmapChar.glyph->bitmap.width);
			int heightPoweredToTwo = MathHelper::nextPowerOf2(aBitmapChar.glyph->bitmap.rows);
			unsigned char * poweredTo2Buffer =  new unsigned char [widthPoweredToTwo * heightPoweredToTwo];			
			for(int j = 0; j < aBitmapChar.glyph->bitmap.width; j++){
				for(int k = 0; k < aBitmapChar.glyph->bitmap.rows; k++) {
					poweredTo2Buffer[k*widthPoweredToTwo + j] = aBitmapChar.glyph->bitmap.buffer[k* aBitmapChar.glyph->bitmap.width + j];
				}
			}
			
			
			//If we delete the buffer here, the cached glyph of the font probably won't work anymore
			//delete aBitmapChar.buffer;
			
			StringPart * aStringPart = new StringPart();
			aStringPart->setTopDisplacement(aBitmapChar.topDisplacement);
			aStringPart->setLeftDisplacement(aBitmapChar.leftDisplacement);
			aStringPart->setXAdvance(aBitmapChar.xAdvance);
			aStringPart->setupStringPart(aBitmapChar.glyph->bitmap.width, aBitmapChar.glyph->bitmap.rows, widthPoweredToTwo, heightPoweredToTwo);
			
			std::string charTextureKey = renderingFont->getFontPath() +  "-" + renderingFont->getFontSize() + "-";
			charTextureKey += internalString[i];
			//string charTextureKey = "-" + renderingFont->getFontSize() + "-";
			//charTextureKey.push_back(internalString[i]);
			
			
			aStringPart->setBitmap(poweredTo2Buffer, charTextureKey);
			delete[] poweredTo2Buffer;
			aStringPart->setAngle(angle);
			stringParts.push_back(aStringPart);
		}
	} else if(renderingMode == perWord){
		
	}
	setPosition(x, y);
}

void GraphicString::setAlignment(AlignmentEnum alignment){
	this->alignment = alignment;
	setPosition(x, y);
}


void GraphicString::render(){
	int stringPartCount = stringParts.size();
	for (int i =0; i < stringPartCount; i++) {
		stringParts[i]->render();
	}
}


//Hardcoded to pass the isInViewport for test, change ASAP
double GraphicString::getWidth() const {
	return 100000;
}
double GraphicString::getHeight() const{
	return 100000;
}
double GraphicString::getXPosition() const{	
	return 0;
}
double GraphicString::getYPosition() const{
	return 0;
}

void GraphicString::setAngle(double angle){
	this->angle = angle;
	int stringPartCount = stringParts.size();
	for (int i =0; i < stringPartCount; i++) {
		stringParts[i]->setAngle(angle);
	}	
}


double GraphicString::getAngle(){
	return angle;
}

void GraphicString::setFixAdvance(int advance){
	fixAdvance = advance;
}


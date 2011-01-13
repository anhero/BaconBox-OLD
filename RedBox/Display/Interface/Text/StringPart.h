#ifndef __STRINGPART_H
#define __STRINGPART_H
#include "OpenGLStringPartDrawer.h"
#include <string>

namespace RedBox {
	class OpenGLStringPartDrawer;
	
	class StringPart  {
	private:
		int x;
		int y;
		int width;
		int height;
		OpenGLStringPartDrawer * drawer;
		int xAdvance; //xAdvance of this char 
		int totalXAdvance; //xAdvance from the beginning of the string
		int topDisplacement;
		int leftDisplacement;
		double angle;
	public:
		StringPart();
		~StringPart();
		void setTopDisplacement(int displacement);
		int getTopDisplacement();
		
		void setLeftDisplacement(int displacement);
		int getLeftDisplacement();

		void setXAdvance(int advance);
		int getXAdvance();
		
		void setTotalXAdvance(int advance);
		int getTotalXAdvance();
		
		
		void setAngle(double angle);
		double getAngle();
		
		void setBitmap(unsigned char * bitmap, const std::string& key);
		
		
		void setXPosition(int x);
		void setYPosition(int y);
		void setupStringPart(int width, int height, int textureWidth, int textureHeight);
		int getXPosition();
		int getYPosition();
		int getWidth();
		int getHeight();
		void render();
	};
}
#endif
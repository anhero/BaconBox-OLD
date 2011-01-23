/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef __GRAPHICCHAR_H
#define __GRAPHICCHAR_H

#include "OpenGLCharDrawer.h"

namespace RedBox {
	/**
     * @ingroup TextDisplay
     */
	class GraphicChar {
	private:
		OpenGLCharDrawer renderedChar;
		int xAdvance;
		int xOffset;
		int yOffset;
	public:
		GraphicChar();
		void render();
		void setPosition(int x, int y);
		void setAngle(int angle);
		void setSize(int width, int height);
		void setFilename(const std::string& path);
		void setTexCoord(float minX, float maxX, float minY, float maxY, int imageWidth, int imageHeight);
		void setXOffset(int offset);
		void setYOffset(int offset);
		void setXAdvance(int advance);
		
		int getXOffset();
		int getYOffset();
		int getXAdvance();
		int getWidth();
		int getHeight();
	};
	
}

#endif

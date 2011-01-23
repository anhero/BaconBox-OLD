/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef __GRAPHICSTRING_H
#define __GRAPHICSTRING_H

#define NO_FIX_ADVANCE -1

#include "Font.h"
#include "Renderable.h"
#include <vector>
#include "StringPart.h"
#include "MathHelper.h"
#include <sstream>
namespace RedBox {
	/**
     * @ingroup TextDisplay
     */
	enum AlignmentEnum {
		leftAlign, rightAlign
	};
	/**
     * @ingroup TextDisplay
     */
	enum RenderMode{
		perLetter, perWord
	};
    
	/**
     * @ingroup TextDisplay
     */
	class GraphicString : public Renderable {
	private:
		std::vector<StringPart*> stringParts;
		RenderMode renderingMode;
		AlignmentEnum alignment;
		std::wstring internalString;
		Font * renderingFont;
		int x, y;
		double angle;
		int fixAdvance;
		
		
		void generateGraphicString();
		
		void cleanStringParts();
	public:
		GraphicString();
		~GraphicString();
		double getWidth() const;
		double getHeight() const;
		
		double getXPosition() const;
		double getYPosition() const;
		void setXPosition(int x);
		void setYPosition(int y);
		void setPosition(int x, int y);
		
		void setAngle(double angle);
		double getAngle();
		
		void setFixAdvance(int advance);
		
		void setFont(Font * aFont);
		void setAlignment(AlignmentEnum alignment);
		void setText(const std::wstring & aString);
		void setText(std::wstringstream & aStringStream);
		void setRenderingMode(RenderMode renderMode);
		void render();
	};
	
}

#endif

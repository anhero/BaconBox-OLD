/**
 * @file
 * @ingroup TextDisplay
 */

#ifndef RB_STRINGFX_H
#define RB_STRINGFX_H
#include "Vec2.h"

namespace RedBox{
	/** 
	 * The string effect type. 
     * @ingroup TextDisplay
     */
	enum StringFXMode{
		///noFx mean no effect.
		noFX,
		
		/**
		 * NOT YET IMPLEMENTED
		 * DropShadow will print a copy of the string under the 
		 * the actual string. The copy can be offset, have a distinct color and size
		 * from the actual string.
		 */
		dropShadow,
		
		/**
		 * NOT YET IMPLEMENTED
		 * OuterGlow will print a copy of the string under the
		 * actual string. The copy is scale by the scaleFactor of the
		 * StringFX class.
		 */
		outerGlow
	};
	
	/** 
	 * A StringFX contains data about an effect applied to a GraphicString.
	 * It is used by GraphicString while rendering. 
	 * The kind of effect could be drop shadow, outer glow, etc.
     * @ingroup TextDisplay
     */
	class StringFX{
	public:
		/**
		 * Set the type of string effect with the StringFXMode enum.
		 */
		void setMode(StringFXMode mode);
		
		/**
		 * Return an StringFXMode enum which tell the type of string effect applied.
		 */
		StringFXMode getMode();
		
		/**
		 * Set the color of the string effect
		 * @param color Must be a pointer to the first value 
		 * of an array of 4 int (int[4]). The format is RGBA. The value
		 * range is 0 to 255.
		 * 
		 */
		void setColor(int * color);
		
		/** 
		 * Set the color of the string effect.
		 * @oaram red Red component of the color. The range is 0 to 255.
		 * @oaram green Green component of the color. The range is 0 to 255.
		 * @oaram blue Blue component of the color. The range is 0 to 255.
		 * @oaram alpha Alpha component of the color. The range is 0 to 255.
		 */
		void setColor(int red, int green, int blue, int alpha);
		
		/**
		 * Return an array containing the color of the string effect.
		 * @return A pointer to the first value of an array containing the
		 * RGBA components of the string effect. Range is from 0 to 255.
		 * The order is Red Green Blue Alpha.
		 */
		int * getColor();
		
		/**
		 * Set the direction vector of the effect. 
		 * Ex. A drop shadow with a direction vector of x:1 y:2 will
		 * offset the shadow 1 pixel to the right and 2 pixels down.
		 */
		void setDirectionVector(Vec2 & directionVector);
		/**
		 * Get the direction vector of the effect
		 * Ex. A drop shadow with a direction vector of x:1 y:2 will
		 * offset the shadow 1 pixel to the right and 2 pixels down.
		 */
		Vec2 getDirectionVector();
	private:
		///The string effect type. 
		StringFXMode mode;
		
		/** 
		 * Color of the string effect. 
		 * The format is an array of int ranging from 0 to 255 
		 * representing (in this order the RGBA value.
		 */
		int color[4];
		
		/**
		 * direction vector of the effect
		 * Ex. A drop shadow with a direction vector of x:1 y:2 will
		 * offset the shadow 1 pixel to the right and 2 pixels down.
		 */
		Vec2 directionVector;
		
	};
}

#endif

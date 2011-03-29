/**
 * @file
 * @ingroup Display
 */

#ifndef RB_PIXMAP_H
#define RB_PIXMAP_H

#include "ColorFormat.h"
namespace RedBox{
	/** 
	 * A PixMap (pixel map) is a buffer (C array) representing a 2D graphic texture.
	 * It is not necessarily formated as RGBA. It can be only alpha value or w/e.
	 * But it will always default to RGBA with a range from 0 to 255 for each color component.
     * @ingroup Display
     */
	class PixMap{
	public:
		/**
		 * Constructor.
		 * @param width width of the PixMap.
		 * @param height Height of the PixMap.
		 * @param colorFormat Color format of the buffer, it default to RGBA. (See the ColorFormat enum)
		 */
		PixMap(int width, int height, ColorFormat colorFormat = RGBA);
		
		/**
		 * Constructor. Create the PixMap with an existing buffer.
		 * It does not copy the buffer, it use the same one, so 
		 * don't delete the original buffer if you are still
		 * using a pixmap object constructed by this version of the constructor.
		 * @param buffer the buffer that will be used as pixmap.
		 * @param width width of the PixMap.
		 * @param height Height of the PixMap.
		 * @param colorFormat Color format of the buffer, it default to RGBA. (See the ColorFormat enum)
		 */
		PixMap(uint8_t * buffer, int width, int height, ColorFormat colorFormat = RGBA);

		
		///Destructor
		~PixMap();
		
		///Return the width of the PixMap
		int getWidth();
		
		///Return the height of the PixMap
		int getHeight();
		
		///Return the colorFormat (See the ColorFormat enum)
		ColorFormat getColorFormat();
		
		///Return a pointer to the first value of the array.
		uint8_t * getBuffer();
		
		/**
		 *	Insert a sub pixmap into the current pixmap.
		 * Both pixmap must have the same color format or the merge
		 * won't work.
		 * The current pixmap must be big enough to insert the sub pixmap or some 
		 * some part of the sub pixmap will be cut out.
		 * @param subPixMap Sub pixmap we want to insert into the current pixmap.
		 * @param xOffset The horizontal position were we want to insert the sub pixmap. (0 correspond to the left 
		 * side of the current pixmap.)
		 * @param yOffset The vertical position were we want to insert the sub pixmap. (0 correspond to the top 
		 * side of the current pixmap.)
		 */
		void insertSubPixMap(PixMap * subPixMap, int xOffset = 0, int yOffset = 0);
	private:
		/**
		 *	Insert a sub pixmap into the current pixmap.
		 * BOTH PIXMAP MUST HAVE THE SAME COLOR FORMAT OR YOUR EYES WILL BURN.
		 * To protect the user this function is private and called by the public version
		 * which compare the color formats before doing the merge.
		 * The current pixmap must be big enough to insert the sub pixmap or some 
		 * some part of the sub pixmap will be cut out.
		 * @param subBuffer buffer of the pixmap we want to insert.
		 * @param width Width of the sub pixmap we want to insert.
		 * @param height Height of the sub pixmap we want to insert.
		 * @param xOffset The horizontal position were we want to insert the sub pixmap. (0 correspond to the left 
		 * side of the current pixmap.)
		 * @param yOffset The vertical position were we want to insert the sub pixmap. (0 correspond to the top 
		 * side of the current pixmap.)
		 */
		void insertSubPixMap(uint8_t * subBuffer, int width, int height, int xOffset, int yOffset);
		
		///Width of the PixMap
		int width;
		
		///Height of the PixMap
		int height;
		
		///Color format of the array (See ColorFormat enum) 
		ColorFormat colorFormat;
		
		///Pointer to the first pixel of the PixMap
		uint8_t * buffer;
	};
}

#endif

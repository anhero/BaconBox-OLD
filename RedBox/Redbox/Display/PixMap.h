/**
 * @file
 * @ingroup Display
 */
#ifndef RB_PIX_MAP_H
#define RB_PIX_MAP_H

#include <stdint.h>

#include "Object.h"
#include "ColorFormat.h"

namespace RedBox {
	/**
	 * A PixMap (pixel map) is a buffer (C array) representing a 2D graphic
	 * texture. It is not necessarily formated as RGBA. It can be only alpha
	 * value or w/e. But it will always default to RGBA with a range from 0 to
	 * 255 for each color component.
	 * @ingroup Display
	 */
	class PixMap : public Object {
	public:
		/**
		 * Default constructor.
		 */
		PixMap();

		/**
		 * Copy constructor.
		 * @param src PixMap to make a copy of.
		 */
		PixMap(const PixMap& src);

		/**
		 * Parameterized constructor.
		 * @param newWidth Width of the PixMap.
		 * @param newHeight Height of the PixMap.
		 * @param newColorFormat Color format of the buffer, it defaults to
		 * RGBA.
		 * @see RedBox::PixMap::width
		 * @see RedBox::PixMap::height
		 * @see RedBox::ColorFormat::Enum
		 */
		PixMap(unsigned int newWidth, unsigned int newHeight,
			   ColorFormat newColorFormat = ColorFormat::RGBA);

		/**
		 * Constructor. Creates the PixMap with an existing buffer. It does not
		 * copy the buffer, it use the same one, so don't delete the original
		 * buffer if you are still using a pixmap object constructed by this
		 * version of the constructor.
		 * @param newBuffer the buffer that will be used as pixmap.
		 * @param newWidth width of the PixMap.
		 * @param newHeight Height of the PixMap.
		 * @param newColorFormat Color format of the buffer, it default to RGBA.
		 * (See the ColorFormat enum)
		 */
		PixMap(uint8_t* newBuffer, unsigned int newWidth,
			   unsigned int newHeight,
			   ColorFormat newColorFormat = ColorFormat::RGBA);

		/**
		 * Destructor.
		 */
		~PixMap();

		/**
		 * Assignation operator overload.
		 * @param src PixMap to make a copy of.
		 */
		PixMap& operator=(const PixMap& src);

		/**
		 * Gets the PixMap's width.
		 * @return PixMap's width (in pixels).
		 * @see RedBox::PixMap::width
		 */
		unsigned int getWidth() const;

		/**
		 * Gets the PixMap's height.
		 * @see RedBox::PixMap::height
		 * @return PixMap's height (in pixels).
		 */
		unsigned int getHeight() const;

		/**
		 * Gets the PixMap's color format.
		 * @return PixMap's corlor format.
		 * @see RedBox::PixMap::colorFormat
		 * @see RedBox::ColorFormat::Enum
		 */
		ColorFormat getColorFormat() const;

		/**
		 * Gets the buffer.
		 * @return Pointer to the buffer's first element.
		 * @see RedBox::PixMap::buffer
		 */
		uint8_t* getBuffer();

		/**
		 * Insert a sub pixmap into the current pixmap.
		 * Both pixmap must have the same color format or the merge
		 * won't work.
		 * The current pixmap must be big enough to insert the sub pixmap or a
		 * part of the sub pixmap will be cut out.
		 * @param subPixMap Sub pixmap we want to insert into the current
		 * pixmap.
		 * @param xOffset The horizontal position were we want to insert the sub
		 * pixmap. (0 correspond to the left
		 * side of the current pixmap.)
		 * @param yOffset The vertical position were we want to insert the sub
		 * pixmap. (0 correspond to the top
		 * side of the current pixmap.)
		 */
		void insertSubPixMap(PixMap* subPixMap, unsigned int xOffset = 0,
		                     unsigned int yOffset = 0);
        
        
        ///Convert the current PixMap to the given format.
        void convertTo(ColorFormat colorFormat);
	private:
		/// Width of the PixMap
		unsigned int width;

		/// Height of the PixMap
		unsigned int height;

		/// Color format of the array (See ColorFormat enum)
		ColorFormat colorFormat;

		/// Pointer to the first pixel of the PixMap
		uint8_t* buffer;

		/**
		 * Insert a sub pixmap into the current pixmap.
		 * BOTH PIXMAP MUST HAVE THE SAME COLOR FORMAT OR YOUR EYES WILL BURN.
		 * To protect the user this function is private and called by the public
		 * version which compares the color formats before doing the merge.
		 * The current pixmap must be big enough to insert the sub pixmap or a
		 * part of the sub pixmap will be cut out.
		 * @param subBuffer buffer of the pixmap we want to insert.
		 * @param subWidth Width of the sub pixmap we want to insert.
		 * @param subHeight Height of the sub pixmap we want to insert.
		 * @param xOffset The horizontal position were we want to insert the sub
		 * pixmap. (0 correspond to the left
		 * side of the current pixmap.)
		 * @param yOffset The vertical position were we want to insert the sub
		 * pixmap. (0 correspond to the top side of the current pixmap.)
		 */
		void insertSubPixMap(uint8_t* subBuffer, unsigned int subWidth,
		                     unsigned int subHeight, unsigned int xOffset,
		                     unsigned int yOffset);
	};
}

#endif

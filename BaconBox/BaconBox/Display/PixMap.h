/**
 * @file
 * @ingroup Display
 */
#ifndef RB_PIX_MAP_H
#define RB_PIX_MAP_H

#include <stdint.h>

#include "BaconBox/Display/ColorFormat.h"

namespace BaconBox {
	class Color;
	/**
	 * A PixMap (pixel map) is a buffer (C array) representing a 2D graphic
	 * texture. It is not necessarily formated as RGBA. It can be only alpha
	 * value or w/e. But it will always default to RGBA with a range from 0 to
	 * 255 for each color component.
	 * @ingroup Display
	 */
	class PixMap {
	public:
		/**
		 * Default constructor.
		 */
		PixMap();

		/**
		 * Copy constructor.
		 * @param src PixMap to make a copy of.
		 */
		PixMap(const PixMap &src);

		/**
		 * Parameterized constructor.
		 * @param newWidth Width of the PixMap.
		 * @param newHeight Height of the PixMap.
		 * @param newColorFormat Color format of the buffer, it defaults to
		 * RGBA.
		 * @see BaconBox::PixMap::width
		 * @see BaconBox::PixMap::height
		 * @see BaconBox::ColorFormat::Enum
		 */
		PixMap(unsigned int newWidth, unsigned int newHeight,
		       ColorFormat newColorFormat = ColorFormat::RGBA);

		/**
		 * Parameterized constructor.
		 * @param newWidth Width of the PixMap.
		 * @param newHeight Height of the PixMap.
		 * @param newColorFormat Color format of the buffer, it defaults to
		 * RGBA.
		 * @param defaultValue Value to set to all of the buffer's data.
		 * @see BaconBox::PixMap::width
		 * @see BaconBox::PixMap::height
		 * @see BaconBox::ColorFormat::Enum
		 */
		PixMap(unsigned int newWidth, unsigned int newHeight,
			   uint8_t defaultValue,
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
		PixMap(uint8_t *newBuffer, unsigned int newWidth,
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
		PixMap &operator=(const PixMap &src);

		/**
		 * Gets the PixMap's width.
		 * @return PixMap's width (in pixels).
		 * @see BaconBox::PixMap::width
		 */
		unsigned int getWidth() const;

		/**
		 * Gets the PixMap's height.
		 * @see BaconBox::PixMap::height
		 * @return PixMap's height (in pixels).
		 */
		unsigned int getHeight() const;

		/**
		 * Gets the PixMap's color format.
		 * @return PixMap's corlor format.
		 * @see BaconBox::PixMap::colorFormat
		 * @see BaconBox::ColorFormat::Enum
		 */
		ColorFormat getColorFormat() const;

		/**
		 * Gets the buffer.
		 * @return Pointer to the buffer's first element.
		 * @see BaconBox::PixMap::buffer
		 */
		uint8_t *getBuffer();

		/**
		 * Gets the buffer.
		 * @return Pointer to the buffer's first element.
		 * @see BaconBox::PixMap::buffer
		 */
		const uint8_t *getBuffer() const;

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
		void insertSubPixMap(const PixMap &subPixMap, unsigned int xOffset = 0,
		                     unsigned int yOffset = 0);

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
		void insertSubPixMap(const uint8_t *subBuffer, unsigned int subWidth,
							 unsigned int subHeight, unsigned int xOffset,
							 unsigned int yOffset);

		///Convert the current PixMap to the given format.
		void convertTo(ColorFormat colorFormat);

		/**
		 * Makes the specified color transparent. Does nothing if the PixMap
		 * has a color format of ALPHA.
		 * @param transparentColor Color to make transparent. All texels that
		 * have the same RGB value as this color will be set to black with an
		 * alpha value of 0.
		 */
		void makeColorTransparent(const Color &transparentColor);
	private:
		/// Width of the PixMap
		unsigned int width;

		/// Height of the PixMap
		unsigned int height;

		/// Color format of the array (See ColorFormat enum)
		ColorFormat colorFormat;

		/// Pointer to the first pixel of the PixMap
		uint8_t *buffer;
	};
}

#endif

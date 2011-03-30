/**
 * @file
 * @ingroup Display
 */

#ifndef RB_COLORFORMAT_H
#define RB_COLORFORMAT_H

namespace RedBox{
	/** 
	 * Enum type representing the color component format.
	 * Used internally to interpret buffers values.
     * @ingroup Display
     */
	enum ColorFormat{
		RGBA,
		Alpha
	};
}

#endif
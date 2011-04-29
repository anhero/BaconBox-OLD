/**
 * @file
 */

#ifndef RB_SIDEENUM_H
#define RB_SIDEENUM_H

namespace RedBox{
	/** 
	 * This enum is used to indicated side related stuff EX. which side collide, which side can collide, etc.
     */
	enum Side{
		left = 1,
		right = 2,
		top = 4,
		bottom = 8,
		all = left | right | top | bottom,
		
	};
}

#endif

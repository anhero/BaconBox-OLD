/**
 * @file
 */
#ifndef RB_SIDE_H
#define RB_SIDE_H

#include "SafeEnum.h"

namespace RedBox {
	struct SideDef {
		enum type {
			/**
			 * Left Side flag. Side flag are used to indicated on which side a
			 * collision occured or to tell the engine which side are collidable.
			 */
			LEFT,
			/**
			 * Right Side flag. Side flag are used to indicated on which side a
			 * collision occured or to tell the engine which side are collidable.
			 */
			RIGHT,
			/**
			 * Top Side flag. Side flag are used to indicated on which side a
			 * collision occured or to tell the engine which side are collidable.
			 */
			TOP,
			/**
			 * Bottom RB_SIDE flag. Side flag are used to indicated on which side a
			 * collision occured or to tell the engine which side are collidable.
			 */
			BOTTOM
		};
	};
	/**
	 * Container for side flag. Side flags are used to indicated on
	 * which side a collision occured or to tell the engine which side are
	 * collidable.
	 */
	typedef SafeEnum<SideDef> Side;
}

#endif

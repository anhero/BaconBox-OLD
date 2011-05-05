/**
 * @file
 */
#ifndef RB_SIDE_H
#define RB_SIDE_H

namespace RedBox {
	/**
	 * Container for side flag. Side flag are used to indicated on
	 * which side a collision occured or to tell the engine which side are
	 * collidable.
	 */
	namespace Side {
		typedef unsigned int Enum;
		/**
		 * Left Side flag. Side flag are used to indicated on which side a
		 * collision occured or to tell the engine which side are collidable.
		 */
		const Enum LEFT = 1;
		/**
		 * Right Side flag. Side flag are used to indicated on which side a
		 * collision occured or to tell the engine which side are collidable.
		 */
		const Enum RIGHT = 2;
		/**
		 * Top Side flag. Side flag are used to indicated on which side a
		 * collision occured or to tell the engine which side are collidable.
		 */
		const Enum TOP = 4;
		/**
		 * Bottom RB_SIDE flag. Side flag are used to indicated on which side a
		 * collision occured or to tell the engine which side are collidable.
		 */
		const Enum BOTTOM = 8;
		/**
		 * All Side flags. Side flags are used to indicated on which side a
		 * collision occured or to tell the engine which side are collidable.
		 */
		const Enum ALL = LEFT | RIGHT | TOP | BOTTOM;
	}
}

#endif

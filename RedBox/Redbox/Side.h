/**
 * @file
 */

#ifndef RB_SIDE_H
#define RB_SIDE_H

namespace RedBox{
	/**
	 * Container for side flag. Side flag are used to indicated on 
	 * which side a collision occured or to tell the engine which side are collidable.
	 */
	typedef int RB_SIDE;
	namespace Side {
		///left RB_SIDE flag. Side flag are used to indicated on which side a collision occured or to tell the engine which side are collidable.
		static const int LEFT = 1;
		///right RB_SIDE flag. Side flag are used to indicated on which side a collision occured or to tell the engine which side are collidable.
		static const int RIGHT = 2;
		///top RB_SIDE flag. Side flag are used to indicated on which side a collision occured or to tell the engine which side are collidable.
		static const int TOP = 4;
		///bottom RB_SIDE flag. Side flag are used to indicated on which side a collision occured or to tell the engine which side are collidable.
		static const int BOTTOM = 8;
		///All RB_SIDE flag (cointain all RB_SIDE flags). Side flag are used to indicated on which side a collision occured or to tell the engine which side are collidable.
		static const int ALL = LEFT | RIGHT | TOP | BOTTOM;
	}   
		

}

#endif

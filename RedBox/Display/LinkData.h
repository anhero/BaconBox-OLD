/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */

#include "PlatformFlagger.h"

#ifdef RB_PHYSICS_ENABLED
#ifndef RB_LINK_DATA_H
#define RB_LINK_DATA_H

#include <iostream>

namespace RedBox {
	/**
	 * Contains the information about a Link.
	 * @ingroup Display
	 * @ingroup Physics
	 */
	struct LinkData {
        /**
         * Outputs the LinkData's content.
         * @param output The ostream in which LinkData is output.
         * @param l LinkData to output in the ostream.
         * @return Resulting ostream.
         */
		friend std::ostream& operator<<(std::ostream& output,
										const LinkData& l);
		/**
		 * Default constructor.
		 */
		LinkData();
		/**
		 * Parameterized constructor.
		 * @param newLength Starting length for the link.
		 * @param newFrontMaxAngle Starting frontal maximum angle.
		 * @param newFrontMinAngle Starting frontal minimum angle.
		 * @param newBackMaxAngle Starting rear maximum angle.
		 * @param newBackMinAngle Starting rear minimum angle
		 */
		LinkData(float newLength, 
				 float newFrontMaxAngle,
				 float newFrontMinAngle,
				 float newBackMaxAngle, 
				 float newBackMinAngle);
		/// Link's length, in dots.
		float length;
		/// Link's maximum angle it can have at the front.
		float frontMaxAngle;
		/// Link's mimimum anlge it can have at the front.
		float frontMinAngle;
		/// Link's maximum angle it can have at the rear.
		float backMaxAngle;
		/// Link's mimimum anlge it can have at the rear.
		float backMinAngle;
	};
}
#endif
#endif
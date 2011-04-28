/**
 * @file
 * @ingroup Helper
 */

#ifndef RB_SPRITE_FACTORY_H
#define RB_SPRITE_FACTORY_H

#include "Color.h"

namespace RedBox {
	class Sprite;
	/**
	 * Factory that constructs sprites.
	 * @ingroup Helper
	 */
	class SpriteFactory {
	public:
		/**
		 * Constructs a polygon. The polygon will be constructed using the
		 * number of sides and side length recieved in the parameters. The
		 * polygons constructed are always regular.
		 * @param nbSides Number of sides the polygon will have.
		 * @param sideLength Length the polygon will have (in points).
		 * @return Pointer to the sprite constructed.
		 */
		static Sprite* makePolygon(unsigned int nbSides, float sideLength,
								   const Color& color);
	private:
		/// Constant for PI.
		static const float PI;
		/// Constant used for converting degrees to radians.
		static const float DEGREE_TO_RADIAN;
		/**
		 * Converts degrees to radians.
		 * @param degree Angle in degrees to convert to radians.
		 * @return Angle in radians converted from the degrees recieved.
		 */
		static inline float degreeToRadian(float degree);
		SpriteFactory();
		~SpriteFactory();
	};
}

#endif

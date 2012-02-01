/**
 * @file
 * @ingroup Helper
 */

#ifndef RB_SPRITE_FACTORY_H
#define RB_SPRITE_FACTORY_H

#include "Sprite.h"
#include "InanimateSprite.h"
#include "ShapeFactory.h"
#include "Color.h"

namespace RedBox {
	/**
	 * Factory that constructs sprites.
	 * @ingroup Helper
	 */
	class SpriteFactory {
	public:
		/**
		 * Constructs a polygon. The polygon will be constructed using the
		 * number of sides and side length received in the parameters. The
		 * polygons constructed are always regular.
		 * @param nbSides Number of sides the polygon will have.
		 * @param sideLength Length the polygon will have (in points).
		 * @param color Polygon's color when rendered.
		 * @return Pointer to the sprite constructed.
		 * @tparam A type that is derived from Shapable, Colorable and
		 * RenderModable.
		 */
		template <typename T>
		static T *makeSpecificPolygon(unsigned int nbSides, float sideLength,
		                              const Color &color) {
			T *result = NULL;

			if (nbSides >= 3 && sideLength > 0.0f) {
				result = new T();
				result->getVertices().resize(nbSides);
				ShapeFactory::createRegularPolygon(nbSides, sideLength, Vector2(), &(result->getVertices()));
				result->setColor(color);
				result->setRenderModes(FlagSet<RenderMode>(RenderMode::SHAPE) |
				                       FlagSet<RenderMode>(RenderMode::COLOR));
			}

			return result;
		}

		/**
		 * Constructs a polygon. The polygon will be constructed using the
		 * number of sides and side length received in the parameters. The
		 * polygons constructed are always regular.
		 * @param nbSides Number of sides the polygon will have.
		 * @param sideLength Length the polygon will have (in points).
		 * @param color Polygon's color when rendered.
		 * @return Pointer to the sprite constructed.
		 */
		static Sprite *makePolygon(unsigned int nbSides, float sideLength,
		                           const Color &color);

		/**
		 * Constructs a polygon. The polygon will be constructed using the
		 * number of sides and side length received in the parameters. The
		 * polygons constructed are always regular.
		 * @param nbSides Number of sides the polygon will have.
		 * @param sideLength Length the polygon will have (in points).
		 * @param color Polygon's color when rendered.
		 * @return Pointer to the inanimate sprite constructed.
		 */
		static InanimateSprite *makeInanimatePolygon(unsigned int nbSides,
		                                             float sideLength,
		                                             const Color &color);
	private:
		/**
		 * Default unaccessible constructor. Made private so the class cannot
		 * be instantiated.
		 */
		SpriteFactory();

		/**
		 * Destructor.
		 */
		~SpriteFactory();
	};
}

#endif

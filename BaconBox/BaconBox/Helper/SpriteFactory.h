/**
 * @file
 * @ingroup Helper
 */

#ifndef RB_SPRITE_FACTORY_H
#define RB_SPRITE_FACTORY_H

#include "BaconBox/Display/Sprite.h"
#include "BaconBox/Display/InanimateSprite.h"
#include "BaconBox/Helper/ShapeFactory.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/Emitter/SpriteEmitter.h"

namespace BaconBox {
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
		
		/**
		 * Constructs a sprite emitter representing an explosions.
		 * @param defaultGraphic Pointer to the default graphic the sprite
		 * emitter will use.
		 * @param nbParticlesToShoot Number of particles to shoot when the
		 * sprite emitter explodes. It has to be higher than 0.
		 * @param force Force at which the particles are shot. A variance of 15%
		 * of the force is applied.
		 * @param startingPosition Starting position of the sprite emitter.
		 * @return Pointer to the newly created sprite emitter. NULL if the
		 * number of particles is not greater than 0.
		 */
		static SpriteEmitter *makeExplosion(const SpriteEmitter::ParticleType *defaultGraphic,
											int nbParticlesToShoot, float force,
											const Vector2 &startingPosition);
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

/**
 * @file
 */
#ifndef RB_SPRITE_EMITTER_H
#define RB_SPRITE_EMITTER_H

#include "ParticleEmitter.h"
#include "Layerable.h"
#include "GraphicElement.h"
#include "Collidable.h"

namespace RedBox {
	/**
     * Used to generate a large number of objects and particles on screen and
     * control them in an organic way. Normally used to generate effects such as
     * fire, smoke, sparks etc.
     */
	class SpriteEmitter : public ParticleEmitter<Collidable, GraphicElement<Collidable> >,
		public Layerable {
	public:
		/**
		 * Default constructor.
		 */
		explicit SpriteEmitter(const GraphicElement<Collidable> *newDefaultGraphic = NULL);

		/**
		 * Copy constructor.
		 * @param src SpriteEmitter to make a copy of.
		 */
		SpriteEmitter(const SpriteEmitter &src);

		/**
		 * Destructor.
		 */
		virtual ~SpriteEmitter();

		/**
		 * Assignment operator.
		 * @param src SpriteEmitter to make a copy of.
		 * @return Reference to the modified SpriteEmitter.
		 */
		SpriteEmitter &operator=(const SpriteEmitter &src);
	private:
		/**
		 * Calls the setToBeDeleted(true) method.
		 */
		void done();
	};

}

#endif // RB_SPRITE_EMITTER_H

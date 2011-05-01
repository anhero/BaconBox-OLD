/**
 * @file
 * @ingroup Display
 */

#ifndef RB_SPRITE_EMITTER_H
#define RB_SPRITE_EMITTER_H

#include <vector>
#include <string>

#include "Emitter.h"
#include "Sprite.h"
#include "Random.h"

namespace RedBox {
	/**
	 * Used to generate a large number of objects and particles on screen and 
	 * control them in an organic way. Normally used to generate effects such as
	 * fire, smoke, sparks etc.
	 * @ingroup Display
	 */
	class SpriteEmitter: public Emitter<Sprite> {
	public:
		/**
		 * Default constructor.
		 */
		SpriteEmitter();

		SpriteEmitter(const std::string& keyName);
		/**
		 * Copy constructor.
		 * @param src SpriteEmitter to make a copy of.
		 */
		SpriteEmitter(const SpriteEmitter& src);
		/**
		 * Destructor.
		 */
		~SpriteEmitter();
		/**
		 * Assignation operator overloading.
		 * @param SpriteEmitter to make a copy of.
		 * @return Instance of this SpriteEmitter.
		 */
		SpriteEmitter& operator=(const SpriteEmitter& src);
	private:
		Sprite* defaultSprite;
		/**
		 * Updates the sprite's alpha using the given alpha to add to
		 * the sprite's current alpha value.
		 * @param deltaAlpha Alpha value to add to the sprite's alpha.
		 * @param renderable Sprite to have its alpha updated.
		 */
		void updateAlpha(float deltaAlpha, Sprite* renderable);
		/**
		 * Updates the sprite's size using the given scaling value to add
		 * to the sprite's size scaling.
		 * @param deltaScaling Scaling value to add to the renderable's size.
		 * @param renderable Sprite to have its size updated.
		 */
		void updateScaling(float deltaScaling, Sprite* renderable);
		/**
		 * Initializes a particle's sprite and returns a pointer to it.
		 * @return Pointer to the created sprite.
		 */
		Sprite* initParticle();
		/**
		 * Starts a particle with the information about its generated angle and
		 * shooting force. If the given pointer to the sprite isn't
		 * initialized, it will initialize it.
		 * @param renderable Renderable to have its values initialized to go in
		 * the right direction with the right force.
		 */
		void startParticle(Sprite*& renderable);
		/**
		 * Updates the particle.
		 * @param renderable Pointer to the sprite to update.
		 */
		void updateParticle(Sprite* renderable);
		/**
		 * Renders the particle.
		 * @param renderable Pointer to the sprite to render.
		 */
		void renderParticle(Sprite* renderable);
		/**
		 * Cleans and resets the SpriteEmitter.
		 */
		void clean();
		/**
		 * Makes a copy of the recieved SpriteEmitter.
		 * @param src SpriteEmitter to make a copy of.
		 */
		void copyFrom(const SpriteEmitter& src);
	};
}

#endif

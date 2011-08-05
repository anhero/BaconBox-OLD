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

		/**
		 * Parameterized constructor. Initializes the default sprite from the
		 * specified texture.
		 * @param keyName Name of the texture to load the sprite with.
		 */
		SpriteEmitter(const std::string& keyName);

		/**
		 * Parameterized constructor. Initializes the sprite emitter to use
		 * the given sprite as the default sprite for each particle.
		 * @param newDefaultSprite Pointer to the new default sprite
		 */
		SpriteEmitter(Sprite* newDefaultSprite);

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
		 * @param src SpriteEmitter to make a copy of.
		 * @return Instance of this SpriteEmitter.
		 */
		SpriteEmitter& operator=(const SpriteEmitter& src);

		/**
		 * Sets the sprite emitter's default sprite for each particle.
		 * @param newDefaultSprite New default sprite to use for each particle.
		 */
		void setDefaultSprite(Sprite* newDefaultSprite);

		/**
		 * Gets the default sprite used for each particle.
		 * @return Pointer to the emitter's default sprite.
		 */
		Sprite* getDefaultSprite();

		/**
		 * Creates a copy of the current sprite emitter.
		 * @return Pointer to the new sprite emitter.
		 */
		GraphicBody* clone() const;
	private:
		/// Pointer to the default sprite to make a copy of for each particle.
		Sprite* defaultSprite;

		/**
		 * Updates the sprite's alpha using the given alpha to add to
		 * the sprite's current alpha value.
		 * @param deltaAlpha Alpha value to add to the sprite's alpha.
		 * @param graphicBody Pointer to the Sprite to have its alpha updated.
		 */
		void updateAlpha(int16_t deltaAlpha, Sprite* graphicBody);

		/**
		 * Updates the sprite's size using the given scaling value to add
		 * to the sprite's size scaling.
		 * @param deltaScaling Scaling value to add to the GraphicBody's size.
		 * @param graphicBody Pointer to the Sprite to have its size updated.
		 */
		void updateScaling(const Vec2& deltaScaling, Sprite* graphicBody);

		/**
		 * Updates the GraphicBody's rotation angle using the given angle to
		 * add to the GraphicBody's rotation angle.
		 * @param deltaAngle Angle value to add to the GraphicBody's rotation
		 * angle.
		 * @param graphicBody GraphicBody to have its rotation angle udpated.
		 */
		void updateRotation(float deltaAngle, Sprite* graphicBody);

		/**
		 * Initializes a particle's sprite and returns a pointer to it.
		 * @return Pointer to the created sprite.
		 */
		Sprite* initParticle();

		/**
		 * Starts a particle with the information about its generated angle and
		 * shooting force. If the given pointer to the sprite isn't
		 * initialized, it will initialize it.
		 * @param graphicBody GraphicBody to have its values initialized to go in
		 * the right direction with the right force.
		 */
		void startParticle(Sprite*& graphicBody);

		/**
		 * Updates the particle.
		 * @param graphicBody Pointer to the sprite to update.
		 */
		void updateParticle(Sprite* graphicBody);

		/**
		 * Renders the particle.
		 * @param graphicBody Pointer to the sprite to render.
		 */
		void renderParticle(Sprite* graphicBody);

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

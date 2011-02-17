/**
 * @file
 * @ingroup Display
 */

#ifndef RB_SPRITE_EMITTER_H
#define RB_SPRITE_EMITTER_H

#include <vector>

#include "Renderable.h"
#include "Sprite.h"

namespace RedBox {
	/**
	 * Used to generate a large number of objects and particles on screen and 
	 * control them in an organic way. Normally used to generate effects such as
	 * fire, smoke, sparks etc.
	 * @ingroup Display
	 */
	class SpriteEmitter: public Renderable {
	public:
		/**
		 * Default constructor.
		 */
		SpriteEmitter();
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
		/**
		 * Renders the SpriteEmitter and its particles.
		 */
		void render();
		/**
		 * Updates the SpriteEmitter and its particles.
		 */
		void update();
		/**
		 * Gets the angle.
		 * @return Floating point number containing the sprite emitter's angle.
		 */
		float getAngle() const;
		/**
		 * Gets the angle variance.
		 * @return Floating point number containing the sprite emitter's angle
		 * variance.
		 */
		float getAngleVariance() const;
		/**
		 * Gets the force.
		 * @return Floating point number containing the sprite emitter's
		 * shooting force.
		 */
		float getForce() const;
		/**
		 * Gets the force variance.
		 * @return Floating point number containing the sprite emitter's
		 * shooting force variance.
		 */
		float getForceVariance() const;
		/**
		 * Gets the particles' lifespan.
		 * @return Floating point number containing the sprite emitter's
		 * particles' lifespan in seconds.
		 */
		float getLifespan() const;
		/**
		 * Gets the particles' lifespan variance.
		 * @return Floating point number containing the sprite emitter's
		 * particles' lifespan variance in seconds.
		 */
		float getLifespanVariance() const;
		/**
		 * Is the sprite emitter active?
		 * @return True if the sprite emitter is active, false if not.
		 */
		bool getIsActive() const;
		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles a sprite emitter can have at the
		 * same time.
		 */
		unsigned int getNbMaxParticles() const;
		
		/**
		 * Sets the angle.
		 * @param newAngle Floating point number containing the new angle.
		 */
		void setAngle(float newAngle);
		/**
		 * Sets the angle variance.
		 * @param newAngleVariance Floating point number containing the new
		 * angle variance.
		 */
		void setAngleVariance(float newAngleVariance);
		/**
		 * Sets the sprite emitter's shooting force.
		 * @param newForce Floating point number containing the sprite emitter's
		 * new shooting force.
		 */
		void setForce(float newForce);
		/**
		 * Sets the sprite emitter's shooting force variance.
		 * @param newForceVariance Floating point number containing the sprite
		 * emitter's new shooting force variance.
		 */
		void setForceVariance(float newForceVariance);
		/**
		 * Sets the particles' lifespan.
		 * @param newLifespan Floating point number containing the particles'
		 * lifespan in seconds.
		 */
		void setLifespan(float newLifespan);
		/**
		 * Sets the particles' lifespan variance.
		 * @param newLifespan Floating point number containing the particles'
		 * lifespan variance in seconds.
		 */
		void setLifespanVariance(float newLifespanVariance);
		/**
		 * Activates or deactivates the sprite emitter.
		 * @param True to activate the sprite emitter, false to deactivate it.
		 */
		void setIsActive(bool newIsActive);
		/**
		 * Activates the sprite emitter. If it is initialized correctly, it will
		 * start emitting.
		 */
		void activate();
		/**
		 * Deactivates the sprite emitter. Stops all particle emitting.
		 */
		void deactivate();
		/**
		 * Sets the maximum number of particles.
		 * @param newNbMaxParticles Maximum number of particles the sprite
		 * emitter can have shown at the same time.
		 * @param baseSprite Pointer to a sprite to use to make a copy of for
		 * each particles.
		 */
		void setNbMaxParticles(unsigned int newNbMaxParticles,
							   Sprite* baseSprite = NULL);
	private:
		struct Particle {
			Particle():sprite(NULL), lifeSpan(0.0f) {};
			Sprite* sprite;
			float lifeSpan;
		};
		std::vector<Particle> particles;
		float angle;
		float angleVariance;
		float force;
		float forceVariance;
		float lifespan;
		float lifespanVariance;
		int nbParticlesToShoot;
		bool isActive;
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
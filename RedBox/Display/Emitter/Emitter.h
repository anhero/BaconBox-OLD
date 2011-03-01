/**
 * @file
 * @ingroup Display
 */
#ifndef RB_EMITTER_H
#define RB_EMITTER_H

#include <vector>

#include "Renderable.h"
#include "ParticleState.h"
#include "ParticlePhase.h"

namespace RedBox {
	/**
	 * @ingroup Display
	 */
	class Emitter: public Renderable {
	public:
		/**
		 * Default constructor.
		 */
		Emitter();
		/**
		 * Copy constructor.
		 * @param src SpriteEmitter to make a copy of.
		 */
		Emitter(const Emitter& src);
		/**
		 * Destructor.
		 */
		~Emitter();
		/**
		 * Assignation operator overloading.
		 * @param Emitter to make a copy of.
		 * @return Instance of this Emitter.
		 */
		Emitter& operator=(const Emitter& src);
		/**
		 * Updates the emitter and its particles.
		 */
		virtual void update();
		/**
		 * Renders the emitter and its particles.
		 */
		virtual void render();
		
		
		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles an emitter can have at the
		 * same time.
		 */
		unsigned int getNbMaxParticles() const;
		/**
		 * Gets the current number of particles.
		 * @return Number of particles currently not dead.
		 */
		unsigned int getNbParticles() const;
		/**
		 * Gets the number of particles to shoot before stopping.
		 * @return Number of particles to shoot before stopping.
		 */
		int getNbParticlesToShoot() const;
		/**
		 * Gets the emitter's lifespan before deactivating itself.
		 * @return Time in seconds the emitter can live.
		 */
		double getLifeSpan() const;
		/**
		 * Gets the time elapsed while the emitter has been active.
		 * @return Time in seconds the emitter has been active.
		 */
		double getElapsedTime() const;
		/**
		 * Is the emitter active?
		 * @return True if the emitter is active, false if not.
		 */
		bool getIsActive() const;
		
		/**
		 * Gets the angle (in degrees) at which the particles will be shot.
		 * @return Angle at which the particles will be shot.
		 */
		float getAngle() const;
		/**
		 * Gets the value (in degrees) by which the angle will vary.
		 * @return Angle variation that the particles will be shot at.
		 */
		float getAngleVariance() const;
		/**
		 * Gets the force at which the particles are shot.
		 * @return Force at which the particles are shot.
		 */
		float getForce() const;
		/**
		 * Gets the force variance at which the particles are shot.
		 * @return Force variance at which the particles are shot.
		 */
		float getForceVariance() const;
		/**
		 * Gets rate at which the particles are shot.
		 * @return Rate at which the particles are shot.
		 */
		double getEmitRate() const;
		/**
		 * Gets the phase information about the birth of a particle.
		 * @return Phase information about the birth of a particle.
		 */
		const ParticlePhase& getBirthPhase() const;
		/**
		 * Gets the phase information about the life of a particle.
		 * @return Phase information about the life of a particle.
		 */
		const ParticlePhase& getLifePhase() const;
		/**
		 * Gets the phase information about the dying phase of a particle.
		 * @return Phase information about the dying phase of a particle.
		 */
		const ParticlePhase& getDyingPhase() const;
		
		
		/**
		 * Sets the maximum number of particles.
		 * @param newNbMaxParticles Maximum number of particles the sprite
		 * emitter can have shown at the same time.
		 */
		void setNbMaxParticles(unsigned int newNbMaxParticles);
		void setNbParticlesToShoot(int newNbParticlesToShoot);
		void setLifeSpan(double newLifeSpan);
		void activate();
		void deactivate();
		
		void setAngle(float newAngle);
		void setAngleVariance(float newAngleVariance);
		void setForce(float newForce);
		void setForceVariance(float newForceVariance);
		void setEmitRate(double newEmitRate);
		void setBirthPhase(const ParticlePhase& newBirthPhase);
		void setLifePhase(const ParticlePhase& newLifePhase);
		void setDyingPhase(const ParticlePhase& newDyingPhase);
	protected:
		virtual Renderable* initParticle()=0;
	private:
		struct Particle {
			Particle();
			Particle(double newTimeLeft, ParticleState::Enum newState,
					 Renderable* newRenderable = NULL);
			double timeLeft;
			ParticleState::Enum state;
			Renderable* renderable;
		};

		std::vector<Particle> particles;
		unsigned int nbParticles;
		int nbParticlesToShoot;
		double lifeSpan;
		double elapsedTime;
		bool isActive;

		float angle;
		float angleVariance;
		float force;
		float forceVariance;
		double emitRate;
		double emitCounter;
		ParticlePhase birthPhase;
		ParticlePhase lifePhase;
		ParticlePhase dyingPhase;
		
		bool shootParticle();
		void clean();
		void copyFrom(const Emitter& src);
	};
}
#endif
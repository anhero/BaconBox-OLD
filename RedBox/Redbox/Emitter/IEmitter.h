/**
 * @file
 * @ingroup Display
 */
#ifndef RB_IEMITTER_H
#define RB_IEMITTER_H

#include "Renderable.h"
#include "ParticlePhase.h"

namespace RedBox {
	/**
	 * Interface for emitters. Abstract class.
	 * @ingroup Display
	 */
	class IEmitter: public Renderable {
	public:
		/**
		 * Default constructor.
		 */
		IEmitter();
		/**
		 * Copy constructor.
		 * @param src Emitter to make a copy of.
		 */
		IEmitter(const IEmitter& src);
		/**
		 * Destructor.
		 */
		virtual ~IEmitter();
		/**
		 * Assignation operator overloading.
		 * @param src Emitter to make a copy of.
		 * @return Instance of this emitter.
		 */
		IEmitter& operator=(const IEmitter& src);
		/**
		 * Updates the emitter and its particles.
		 */
		virtual void update()=0;
		/**
		 * Renders the emitter and its particles.
		 */
		virtual void render()=0;
		
		
		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles an emitter can have at the
		 * same time.
		 */
		virtual unsigned int getNbMaxParticles() const=0;
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
		 * @param newNbMaxParticles Maximum number of particles the emitter can
		 * have shown at the same time.
		 */
		virtual void setNbMaxParticles(unsigned int newNbMaxParticles)=0;
		/**
		 * Sets the number of particles to shoot before deactivating.
		 * @param newNbParticlesToShoot Number of particles to shoot before
		 * stopping. -1 for infinite emitter.
		 */
		void setNbParticlesToShoot(int newNbParticlesToShoot);
		/**
		 * Sets the emitter's life span.
		 * @param newLifeSpan Life span in seconds the emitter will be active.
		 */
		void setLifeSpan(double newLifeSpan);
		/**
		 * Activate the emitter. Will re deactivate itself if the life span or
		 * the number of particles to shoot are at 0. Does nothing if already
		 * active.
		 */
		void activate();
		/**
		 * Deactivates the emitter. It is put on hold and will restart noramlly
		 * when re-activated. Does nothing if already deactivated.
		 */
		void deactivate();
		
		/**
		 * Sets the angle at which the emitter will emit its particles.
		 * @param newAngle Angle (in degrees) at which to shoot the particles.
		 */
		void setAngle(float newAngle);
		/**
		 * Sets the variance for the angle of the particles shot.
		 * @param newAngleVariance Variance (in degrees) affected to the angle
		 * at which the particles are shot.
		 */
		void setAngleVariance(float newAngleVariance);
		/**
		 * Sets the force at which the particles are thrown.
		 * @param newForce Force at which the particles are thrown.
		 */
		void setForce(float newForce);
		/**
		 * Sets the variance added to the force of particles shot.
		 * @param newForceVariance Variance added to the force of particles
		 * shot.
		 */
		void setForceVariance(float newForceVariance);
		/**
		 * Sets the emission rate at which the particles are shot.
		 * @param newEmitRate Rate (in emission per second) at which the
		 * particles are shot.
		 */
		void setEmitRate(double newEmitRate);
		/**
		 * Sets the definition for what happens in the particle's birth phase.
		 * @param newBirthPhase Definition of the effects happening during the
		 * particle's birth phase.
		 */
		void setBirthPhase(const ParticlePhase& newBirthPhase);
		/**
		 * Sets the definition for what happens in the particle's life phase.
		 * @param newLifePhase Definition of the effects happening during the
		 * particle's life phase.
		 */
		void setLifePhase(const ParticlePhase& newLifePhase);
		/**
		 * Sets the definition for what happens in the particle's dying phase.
		 * @param newDyingPhase Definition of the effects happening during the
		 * particle's dying phase.
		 */
		void setDyingPhase(const ParticlePhase& newDyingPhase);
	protected:
		/// Number of particles currently active and being shown.
		unsigned int nbParticles;
		/// Number of particles left to shoot. -1 for infinite.
		int nbParticlesToShoot;
		/// Time in seconds the emitter stays active. -1 for infinite
		double lifeSpan;
		/// Elapsed time the emitter was active for.
		double elapsedTime;
		/// Flag at true if the emitter is active, false if it is not.
		bool isActive;
		
		/// Angle (in degrees) at which the emitter emits particles.
		float angle;
		/**
		 * Angle variance (in degrees) in a cone at which the particles are
		 * emit.
		 */
		float angleVariance;
		/// Force at which the particles are shot.
		float force;
		/// Variance added to the force when the particles are shot.
		float forceVariance;
		/**
		 * Particle emissions per second the emitter will try to shoot. Can be
		 * limited by the maximum nomber of particles shown at the same time.
		 */
		double emitRate;
		/// Used to keep track of the particles emission rate.
		double emitCounter;
		/// Definition of what happens in the particle's birth phase.
		ParticlePhase birthPhase;
		/// Definition of what happens in the particle's life phase.
		ParticlePhase lifePhase;
		/// Definition of what happens in the particle's dying phase.
		ParticlePhase dyingPhase;
		
		
		/**
		 * return emitter's width.
		 */
		virtual float getWidth() const;
		/**
		 * return emitter's height.
		 */
		virtual float getHeight() const;

	private:
		/**
		 * Cleans the emitter. Frees all allocated memory and resets the
		 * emitter.
		 */
		void clean();
		/**
		 * Makes a copy of the given emitter.
		 * @param src Emitter to make a copy of.
		 */
		void copyFrom(const IEmitter& src);
	};
}
#endif
/**
 * @file
 * @ingroup Display
 */
#ifndef RB_IEMITTER_H
#define RB_IEMITTER_H

#include "GraphicBody.h"
#include "ParticlePhase.h"

namespace RedBox {
	/**
	 * Interface for emitters. Abstract class.
	 * @ingroup Display
	 */
	class IEmitter: public GraphicBody {
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
		 * Gets the current number of particles.
		 * @return Number of particles currently not dead.
		 * @see RedBox::IEmitter::nbParticles
		 */
		unsigned int getNbParticles() const;

		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles an emitter can have at the
		 * same time.
		 */
		virtual unsigned int getNbMaxParticles() const = 0;

		/**
		 * Sets the maximum number of particles.
		 * @param newNbMaxParticles Maximum number of particles the emitter can
		 * have shown at the same time on the screen.
		 */
		virtual void setNbMaxParticles(unsigned int newNbMaxParticles) = 0;

		/**
		 * Gets the number of particles to shoot before stopping.
		 * @return Number of particles to shoot before stopping.
		 * @see RedBox::IEmitter::nbParticlesToShoot
		 */
		int getNbParticlesToShoot() const;

		/**
		 * Sets the number of particles to shoot before deactivating.
		 * @param newNbParticlesToShoot Number of particles to shoot before
		 * stopping. -1 for infinite emitter.
		 * @see RedBox::IEmitter::nbParticlesToShoot
		 */
		void setNbParticlesToShoot(int newNbParticlesToShoot);

		/**
		 * Gets the emitter's lifespan before deactivating itself.
		 * @return Time in seconds the emitter can live.
		 * @see RedBox::IEmitter::lifeSpan
		 */
		double getLifeSpan() const;

		/**
		 * Sets the emitter's life span.
		 * @param newLifeSpan Life span in seconds the emitter will be active.
		 * @see RedBox::IEmitter::lifeSpan
		 */
		void setLifeSpan(double newLifeSpan);

		/**
		 * Gets the time elapsed while the emitter has been active.
		 * @return Time in seconds since the emitter has been active.
		 * @see RedBox::IEmitter::elapsedTime
		 */
		double getElapsedTime() const;

		/**
		 * Checks the emitter is started.
		 * @return True if the emitter is active, false if not.
		 */
		bool isStarted() const;
		
		/**
		 * Starts the emitter. Will re deactivate itself if the life span or the
		 * number of particles to shoot are at 0. Does nothing if already
		 * active.
		 */
		void start();

		/**
		 * Stops the emitter. It is put on hold and will restart noramlly when
		 * re-activated. Does nothing if already deactivated.
		 */
		void stop();

		void rotateFromPoint(float rotationAngle, const Vector2& rotationPoint);

		/**
		 * Gets the angle (in degrees) at which the particles will be shot.
		 * @return Angle at which the particles will be shot.
		 * @see RedBox::IEmitter::angle
		 */
		float getShootingAngle() const;

		/**
		 * Sets the angle at which the emitter will emit its particles.
		 * @param newAngle Angle (in degrees) at which to shoot the particles.
		 * @see RedBox::IEmitter::angle
		 */
		void setShootingAngle(float newAngle);

		/**
		 * Gets the value (in degrees) by which the angle will vary.
		 * @return Angle variation that the particles will be shot at.
		 * @see RedBox::IEmitter::angleVariance
		 */
		float getShootingAngleVariance() const;

		/**
		 * Sets the variance for the angle of the particles shot.
		 * @param newAngleVariance Variance (in degrees) affected to the angle
		 * at which the particles are shot.
		 */
		void setShootingAngleVariance(float newAngleVariance);

		/**
		 * Gets the force at which the particles are shot.
		 * @return Force at which the particles are shot.
		 * @see RedBox::IEmitter::force
		 */
		float getForce() const;

		/**
		 * Sets the force at which the particles are thrown.
		 * @param newForce Force at which the particles are thrown.
		 * @see RedBox::IEmitter::force
		 */
		void setForce(float newForce);

		/**
		 * Gets the force variance at which the particles are shot.
		 * @return Force variance at which the particles are shot.
		 * @see RedBox::IEmitter::forceVariance
		 */
		float getForceVariance() const;

		/**
		 * Sets the variance added to the force of particles shot.
		 * @param newForceVariance Variance added to the force of particles
		 * shot.
		 * @see RedBox::IEmitter::forceVariance
		 */
		void setForceVariance(float newForceVariance);

		/**
		 * Gets rate at which the particles are shot.
		 * @return Rate at which the particles are shot.
		 * @see RedBox::IEmitter::emitRate
		 */
		double getEmitRate() const;

		/**
		 * Sets the emission rate at which the particles are shot.
		 * @param newEmitRate Rate (in emission per second) at which the
		 * particles are shot.
		 * @see RedBox::IEmitter::emitRate
		 */
		void setEmitRate(double newEmitRate);

		/**
		 * Gets the phase information about the birth of a particle.
		 * @return Phase information about the birth of a particle.
		 * @see RedBox::IEmitter::birthPhase
		 */
		const ParticlePhase& getBirthPhase() const;

		/**
		 * Sets the definition for what happens in the particle's birth phase.
		 * @param newBirthPhase Definition of the effects happening during the
		 * particle's birth phase.
		 * @see RedBox::IEmitter::birthPhase
		 */
		void setBirthPhase(const ParticlePhase& newBirthPhase);

		/**
		 * Gets the phase information about the life of a particle.
		 * @return Phase information about the life of a particle.
		 * @see RedBox::IEmitter::lifePhase
		 */
		const ParticlePhase& getLifePhase() const;

		/**
		 * Sets the definition for what happens in the particle's life phase.
		 * @param newLifePhase Definition of the effects happening during the
		 * particle's life phase.
		 * @see RedBox::IEmitter::lifePhase
		 */
		void setLifePhase(const ParticlePhase& newLifePhase);

		/**
		 * Gets the phase information about the dying phase of a particle.
		 * @return Phase information about the dying phase of a particle.
		 * @see RedBox::IEmitter::dyingPhase
		 */
		const ParticlePhase& getDyingPhase() const;
		
		/**
		 * Sets the definition for what happens in the particle's dying phase.
		 * @param newDyingPhase Definition of the effects happening during the
		 * particle's dying phase.
		 * @see RedBox::IEmitter::dyingPhase
		 */
		void setDyingPhase(const ParticlePhase& newDyingPhase);

		/**
		 * Tells the emitter to delete itself after it deactivates itself when
		 * the lifespan is over or the number of particles to shoot has been
		 * reached.
		 * @see RedBox::IEmitter::dieOnDeactivate
		 * @see RedBox::IEmitter::dontDeleteOnDeactivate()
		 */
		void deleteOnDeactivate();

		/**
		 * Tells the emitter not to delete itself after it deactivates itself
		 * when the lifespan is over or the number of particles to shoot has
		 * been reached. Must be set before the emitter is done if you want to
		 * be able to re-use it once it's done.
		 * @see RedBox::IEmitter::dieOnDeactivate
		 * @see RedBox::IEmitter::deleteOnDeactivate()
		 */
		void dontDeleteOnDeactivate();

		/**
		 * Gets the emitter's width.
		 * @return Emitter's width, unless overloaded, returns 1.
		 */
		virtual float getWidth() const;

		/**
		 * Gets the emitter's height.
		 * @return Emitter's height, unless overloaded, returns 1.
		 */
		virtual float getHeight() const;

	protected:
		/// Number of particles currently active and being shown on the screen.
		unsigned int nbParticles;

		/// Number of particles left to shoot. -1 for infinite.
		int nbParticlesToShoot;

		/// Time in seconds the emitter stays active. -1 for infinite.
		double lifeSpan;

		/// Elapsed time the emitter was active for.
		double elapsedTime;

		/// Flag at true if the emitter is active, false if it is not.
		bool started;

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

		bool dieOnDeactivate;
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

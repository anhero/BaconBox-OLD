/**
 * @file
 */
#ifndef RB_EMITTER_H
#define RB_EMITTER_H

#include <list>

#include "ParticlePhase.h"

namespace BaconBox {
	/**
     * Represents an emitter. Emitters for specific objects inherit from this
     * class. This class is abstract.
     * @ingroup Display
     */
	class Emitter {
	public:
		/// Represents the type that contains the phases.
		typedef std::list<ParticlePhase> PhaseList;

		/**
		 * Default constructor.
		 */
		Emitter();

		/**
		 * Copy constructor.
		 * @param src Emitter to make a copy of.
		 */
		Emitter(const Emitter &src);

		/**
		 * Destructor.
		 */
		virtual ~Emitter();

		/**
		 * Assignment operator.
		 * @param src Emitter to make a copy of.
		 * @return Reference to the modified Emitter.
		 */
		Emitter &operator=(const Emitter &src);

		/**
		 * Gets the current number of particles.
		 * @return Number of particles currently not dead.
		 * @see BaconBox::Emitter::nbParticles
		 */
		unsigned int getNbParticles() const;

		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles an emitter can have at the
		 * same time.
		 */
		virtual unsigned int getMaximumNbParticles() const = 0;

		/**
		 * Sets the maximum number of particles.
		 * @param newMaximumNbParticles Maximum number of particles the emitter
		 * can have shown at the same time on the screen.
		 */
		virtual void setMaximumNbParticles(unsigned int newMaximumNbParticles) = 0;

		/**
		 * Gets the number of particles to shoot before stopping.
		 * @return Number of particles left to shoot (-1 for infinite).
		 * @see BaconBox::Emitter::nbParticlesToShoot
		 */
		int getNbParticlesToShoot() const;

		/**
		 * Sets the number of particles left to shoot.
		 * @param newNbParticlesToShoot New number of particles left to shoot.
		 * Any negative number will set it to infinit shooting.
		 * @see BaconBox::Emitter::nbParticlesToShoot
		 */
		void setNbParticlesToShoot(int newNbParticlesToShoot);

		/**
		 * Gets the particle emitter's lifespan.
		 * @return Lifespan (not the time remaining, -1 for infinite).
		 * @see BaconBox::Emitter::lifeSpan
		 */
		double getLifeSpan() const;

		/**
		 * Sets the particle emitter's life span.
		 * @param newLifeSpan New life span (any negative number for infinite).
		 * @see BaconBox::Emitter::lifeSpan
		 */
		void setLifeSpan(double newLifeSpan);

		/**
		 * Gets the time (in seconds) elapsed since the emitter was started.
		 * @return Time elapsed since the emitter was started or 0 if the
		 * emitter isn't started or has an infinite life span.
		 * @see BaconBox::Emitter::elapsedTime
		 */
		double getElapsedTime() const;

		/**
		 * Checks whether the particle emitter is started or not.
		 * @return True if the emitter is started, false if not.
		 * @see BaconBox::Emitter::started
		 */
		bool isStarted() const;

		/**
		 * Starts the particle emitter.
		 * @see BaconBox::Emitter::started
		 */
		void start();
		
		/**
		 * Stops the particle emitter.
		 * @see BaconBox::Emitter::started
		 */
		void stop();
		
		/**
		 * Checks whether or not the emitter is an explosion. When started,
		 * an explosion emitter shoots all of its maximum number of particles
		 * at the same time and then stops.
		 * @return True if the emitter is an explosion, false if not.
		 * @see BaconBox::Emitter::explosion
		 */
		bool isExplosion() const;
		
		/**
		 * Sets whether or not the emitter is an explosion. When started,
		 * an explosion emitter shoots all of its maximum number of particles at
		 * the same time and then stops.
		 * @param newExplosion Set this to true if you want the emitter to be an
		 * explosion.
		 * @see BaconBox::Emitter::explosion
		 */
		void setExplosion(bool newExplosion);

		/**
		 * Gets the particle emitter's shooting angle.
		 * @return Particle emitter's shooting angle (value from -180.0f to
		 * 180.0f).
		 * @see BaconBox::Emitter::shootingAngle
		 */
		float getShootingAngle() const;

		/**
		 * Sets the shooting angle.
		 * @param newShootingAngle New shooting angle, wraps it arout to be
		 * within range of -180.0f to 180.0f
		 * @see BaconBox::Emitter::shootingAngle
		 */
		void setShootingAngle(float newShootingAngle);

		/**
		 * Gets the particle emitter's shooting angle variance.
		 * @return Particle emitter's shooting angle (value from 0 to 180).
		 * @see BaconBox::Emitter::shootingAngleVariance
		 */
		float getShootingAngleVariance() const;

		/**
		 * Sets the particle emitter's shooting angle variance.
		 * @param newShootingAngleVariance New shooting angle, clamps it from
		 * 0 to 180.
		 * @see BaconBox::Emitter::shootingAngleVariance
		 */
		void setShootingAngleVariance(float newShootingAngleVariance);

		/**
		 * Gets the particle emitter's shooting force (in velocity, pixels per
		 * second).
		 * @return Shooting force (in pixels per second).
		 * @see BaconBox::Emitter::shootingForce
		 */
		float getShootingForce() const;

		/**
		 * Sets the particle emitter's shooting force.
		 * @param newShootingForce New shooting force (in pixels per second).
		 * @see BaconBox::Emitter::shootingForce
		 */
		void setShootingForce(float newShootingForce);

		/**
		 * Gets the particle emitter's shooting force variance (in velocity,
		 * pixels per second).
		 * @return Shooting force (in pixels per second).
		 * @see BaconBox::Emitter::shootingForceVariance
		 */
		float getShootingForceVariance() const;

		/**
		 * Sets the particle emitter's shooting force variance.
		 * @param newShootingForceVariance New shooting force variance (in
		 * pixels per second).
		 * @see BaconBox::Emitter::shootingForceVariance
		 */
		void setShootingForceVariance(float newShootingForceVariance);

		/**
		 * Gets the time between each spawn.
		 * @return Time between each particle spawning (in seconds). -1 for
		 * a null spawning rate.
		 * @see BaconBox::Emitter::timePerSpawn
		 */
		double getTimeBetweenSpawns() const;

		/**
		 * Gets the number of particles spawned per second.
		 * @return Number of particles spawned per second.
		 * @see BaconBox::Emitter::timePerSpawn
		 */
		double getSpawningRate() const;

		/**
		 * Sets te time between each spawn.
		 * @param newTimePerSpawn New time between each spawning particles
		 * (in seconds). Does nothing if 0 or any negative number except -1 is
		 * received. -1 for a null spawning rate.
		 * @see BaconBox::Emitter::timePerSpawn
		 */
		void setTimeBetweenSpawns(double newTimePerSpawn);

		/**
		 * Sets the number of particles to spawn per second.
		 * @param newSpawningRate Number of particles to spawn per second.
		 * @see BaconBox::Emitter::timePerSpawn
		 */
		void setSpawningRate(double newSpawningRate);

		/**
		 * Gets the list of phases to use for the particles' lives.
		 * @return List of phases.
		 * @see BaconBox::Emitter::phases
		 */
		PhaseList &getPhases();

		/**
		 * Gets the list of phases to use for the particles' lives.
		 * @return List of phases.
		 * @see BaconBox::Emitter::phases
		 */
		const PhaseList &getPhases() const;

		/**
		 * Checks if the particle emitter is to die when done.
		 * @return True if the particle emitter needs to be deleted when done,
		 * false if not.
		 */
		bool isToDeleteWhenDone() const;

		/**
		 * Sets whether the particle emitter needs to die when its lifespan is
		 * done or when it has shot all its particles to shoot.
		 * @param newToDeleteWhenDone If the particle emitter needs to die or
		 * not when done.
		 */
		void setToDeleteWhenDone(bool newToDeleteWhenDone);
	protected:
		/// Elapsed time the emitter was active for.
		double elapsedTime;

		/// Number of particles currently active and being shown on the screen.
		unsigned int nbParticles;

		/// Number of particles left to shoot. -1 for infinite.
		int nbParticlesToShoot;
	private:
		/// Time in seconds the emitter stays active. -1 for infinite.
		double lifeSpan;

		/// Flag at true if the emitter is active, false if it is not.
		bool started;
		
		/// Flag at true if the emitter is an explosion.
		bool explosion;

		/// Angle (in degrees) at which the emitter emits particles.
		float shootingAngle;

		/**
		 * Angle variance (in degrees) in a cone at which the particles are
		 * emit.
		 */
		float shootingAngleVariance;

		/// Force at which the particles are shot (in pixels per second).
		float shootingForce;

		/// Variance added to the force when the particles are shot.
		float shootingForceVariance;

		/**
		 * Time (in seconds) between each particle spawning. -1 for a null
		 * spawning rate.
		 */
		double timePerSpawn;

		/**
		 * List of particle phases each particle go through before dying.
		 */
		PhaseList phases;

		/**
		 * Set to true if the particle emitter is to try to die when done. False
		 * by default. Does not work if the particle emitter is not managed by
		 * a BodyManager.
		 * @see BaconBox::BodyManager
		 */
		bool toDeleteWhenDone;
	};

}

#endif // RB_EMITTER_H

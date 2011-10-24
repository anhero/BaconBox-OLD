/**
 * @file
 */
#ifndef RB_PARTICLE_EMITTER_H
#define RB_PARTICLE_EMITTER_H

#include <cassert>
#include <cmath>

#include <vector>
#include <utility>

#include "MathHelper.h"
#include "Updateable.h"
#include "Maskable.h"
#include "ParticlePhase.h"
#include "Particle.h"
#include "Animatable.h"
#include "Colorable.h"
#include "Collidable.h"
#include "Manageable.h"
#include "IsBaseOf.h"
#include "StaticAssert.h"
#include "IsSame.h"
#include "Emitter.h"
#include "Engine.h"
#include "Random.h"
#include "CallHelper.h"

namespace RedBox {
	/**
	 * Particle emitter. Emits graphic particles. Particles to be emitted must
	 * be animatable, maskable, collidable and colorable.
	 * @tparam Parent Collidable or Transformable.
	 * @tparam ParticleType Type of the particle's grahpic to emit.
	 */
	template <typename Parent, typename ParticleType>
	class ParticleEmitter : virtual public Updateable, virtual public Maskable,
		public Emitter, public Parent {
	public:
		/**
		 * Default constructor.
		 */
		explicit ParticleEmitter(const ParticleType *newDefaultGraphic = NULL) :
			Updateable(), Maskable(), Emitter(), Parent(),
			defaultGraphic(newDefaultGraphic), currentMask(NULL),
			spawningCounter(0.0), particles() {
		}

		/**
		 * Copy constructor.
		 * @param src ParticleEmitter to make a copy of.
		 */
		ParticleEmitter(const ParticleEmitter &src) : Updateable(src),
			Maskable(src), Emitter(src), Parent(src),
			defaultGraphic(src.defaultGraphic), currentMask(src.currentMask),
			spawningCounter(src.spawningCounter), particles(src.particles) {
		}

		/**
		 * Destructor.
		 */
		virtual ~ParticleEmitter() {
			clearParticles();
		}

		/**
		 * Assignment operator.
		 * @param src ParticleEmitter to make a copy of.
		 * @return Reference to the modified ParticleEmitter.
		 */
		ParticleEmitter &operator=(const ParticleEmitter &src) {
			this->Emitter::operator=(src);
			this->Parent::operator=(src);

			if (this != &src) {
				defaultGraphic = src.defaultGraphic;
				currentMask = src.currentMask;
				spawningCounter = src.spawningCounter;
				particles = src.particles;
			}

			return *this;
		}

		/**
		 * Updates the emitter and its particles.
		 */
		virtual void update() {
			// We call the emitter's parent's update method if needed.
			CallUpdate<ParticleEmitter<Parent, ParticleType>, Parent, IsBaseOf<Updateable, Parent>::RESULT>()(this);

			// We make sure the emitter is active and has particles to emit.
			if (isStarted() && getSpawningRate() > 0.0 &&
			    nbParticlesToShoot != 0) {
				spawningCounter += Engine::getSinceLastUpdate();

				// We try to shoot particles as long as the spawning rate lets
				// us.
				while (nbParticlesToShoot != 0 && spawningCounter > getTimeBetweenSpawns() && shootParticle()) {
					if (nbParticlesToShoot > -1) {
						--nbParticlesToShoot;
					}

					spawningCounter -= getTimeBetweenSpawns();
				}

				// We check if we have to count the emitter's life span.
				if (getLifeSpan() != -1.0) {
					// We update the emitter's elapsed time.
					elapsedTime += Engine::getSinceLastUpdate();

					if (getLifeSpan() < elapsedTime) {
						stop();
					}
				}
			}

			// We update the particles that still have time left.
			for (typename ParticleVector::iterator i = particles.begin();
			     i != particles.end(); ++i) {
				// We check if it is still alive.
				if (i->second.timeLeft > 0.0) {
					assert(i->second.graphic);
					// We update the particle.
					i->second.alphaCounter += static_cast<float>(Engine::getSinceLastUpdate()) * i->second.alphaPerSecond;
					int32_t tmp = static_cast<int32_t>(floor(i->second.alphaCounter));
					i->second.graphic->setAlpha(i->second.graphic->getAlpha() + tmp);

					if (tmp > 0) {
						i->second.alphaCounter -= static_cast<double>(tmp);
					}

					if (i->second.scalingPerSecond != Vector2()) {
						i->second.graphic->addToScaling(i->second.scalingPerSecond * static_cast<float>(Engine::getSinceLastUpdate()));
					}

					if (i->second.anglePerSecond != 0.0f) {
						i->second.graphic->rotate(i->second.anglePerSecond * static_cast<float>(Engine::getSinceLastUpdate()));
					}

					// We update the graphic.
					i->second.graphic->update();
					// We update the time left.
					i->second.timeLeft -= Engine::getSinceLastUpdate();
				}

				// We update the particle's phase.
				while (i->second.timeLeft <= 0.0 && i->first != getPhases().end()) {
					++(i->first);

					if (i->first == getPhases().end()) {
						--nbParticles;

					} else {
						startPhase(i);
					}
				}
			}

			if ((nbParticlesToShoot == 0 ||
			     (getLifeSpan() >= 0 && getLifeSpan() < elapsedTime)) &&
			    isToDeleteWhenDone()) {
				bool notFound = true;
				typename ParticleVector::const_iterator i = particles.begin();

				while (notFound && i != particles.end()) {
					if (i->first != getPhases().end()) {
						notFound = false;

					} else {
						++i;
					}
				}

				if (notFound) {
					stop();
					// We set the emitter to be deleted if it is managed.
					done();
				}
			}
		}

		/**
		 * Renders the emitter and its particles.
		 */
		virtual void render() {
			if (isStarted()) {
				for (typename ParticleVector::iterator i = particles.begin();
				     i != particles.end(); ++i) {
					if (i->second.timeLeft > 0.0 && i->second.graphic) {
						i->second.graphic->render();
					}
				}
			}
		}

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		virtual void mask() {
			if (isStarted()) {
				for (typename ParticleVector::iterator i = particles.begin();
				     i != particles.end(); ++i) {
					if (i->second.timeLeft > 0.0 && i->second.graphic) {
						i->second.graphic->mask();
					}
				}
			}
		}

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		virtual void unmask() {
			if (isStarted()) {
				for (typename ParticleVector::iterator i = particles.begin();
				     i != particles.end(); ++i) {
					if (i->second.timeLeft > 0.0 && i->second.graphic) {
						i->second.graphic->unmask();
					}
				}
			}
		}

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		virtual Maskable *getMask() const {
			return currentMask;
		}

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(Maskable *newMask, bool inverted = false) {
			currentMask = newMask;

			for (typename ParticleVector::iterator i = particles.begin();
			     i != particles.end(); ++i) {
				if (i->second.graphic) {
					i->second.graphic->setMask(newMask, inverted);
				}
			}
		}

		using Parent::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see RedBox::Positionable::move(const Vector2& delta);
		 * @see RedBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta) {
			this->Parent::move(xDelta, yDelta);
		}

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		virtual const Vector2 getSize() const {
			return Vector2();
		}

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const {
			return 0.0f;
		}

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const {
			return 0.0f;
		}

		using Parent::scaleFromPoint;

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint) {
			this->Parent::scaleFromPoint(xScaling, yScaling, fromPoint);
		}

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2 &rotationPoint) {
			this->Parent::rotateFromPoint(rotationAngle, rotationPoint);
		}

		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles an emitter can have at the
		 * same time.
		 * @see RedBox::ParticleEmitter<Parent, ParticleType>::particles
		 */
		unsigned int getMaximumNbParticles() const {
			return particles.size();
		}

		/**
		 * Sets the maximum number of particles.
		 * @param newMaximumNbParticles Maximum number of particles the emitter
		 * can have shown at the same time on the screen.
		 * @see RedBox::ParticleEmitter<Parent, ParticleType>::particles
		 */
		void setMaximumNbParticles(unsigned int newMaximumNbParticles) {
			// We make sure to free the memory if we reduce the number of
			// maximum particles.
			if (!particles.empty()) {
				for (typename ParticleVector::size_type i = particles.size() - 1; i >= newMaximumNbParticles; --i) {
					if (particles[i].second.graphic) {
						delete particles[i].second.graphic;
					}
				}
			}

			particles.resize(newMaximumNbParticles);

			for (typename ParticleVector::iterator i = particles.begin(); i != particles.end(); ++i) {
				i->first = getPhases().end();
			}
		}

		/**
		 * Gets the default graphic.
		 * @return Pointer to the default graphic used. NULL if none are
		 * specified.
		 * @see RedBox::ParticleEmitter<Parent, ParticleType>::defaultGraphic
		 */
		const ParticleType *getDefaultGraphic() const {
			return defaultGraphic;
		}

		/**
		 * Sets the default graphic to use. Re-creates the vector of particles
		 * with the new graphic and kills all active particles (if the
		 * received new default graphic is different).
		 * @param newDefaultGraphic Pointer to the new default graphic to use.
		 * Can be NULL, but the emitter will continue if it was started, but
		 * will not emit anything.
		 * @see RedBox::ParticleEmitter<Parent, ParticleType>::defaultGraphic
		 */
		void setDefaultGraphic(const ParticleType *newDefaultGraphic) {
			// We make sure the new default graphic is different.
			if (newDefaultGraphic != defaultGraphic) {
				// We take note of the current maximum number of particles.
				typename ParticleVector::size_type tmpMaximumNbParticles = particles.size();
				// We clear all the particles.
				clearParticles();
				particles.clear();
				// We re-set the maximum number of particles.
				particles.resize(tmpMaximumNbParticles);
				// We reset the number of active particles.
				nbParticles = 0;
			}
		}

	protected:
		/**
		 * Called when the particle emitter is ready to be deleted. Must be
		 * overriden to take the necessary actions to delete the particle
		 * emitter.
		 */
		virtual void done() {
		}

	private:
		/// Makes sure the particles are collidable (thus updateable too).
		typedef typename StaticAssert<IsBaseOf<Collidable, ParticleType>::RESULT>::Result AreParticlesCollidable;

		/// Makes sure the particles are animatable
		typedef typename StaticAssert<IsBaseOf<Animatable, ParticleType>::RESULT>::Result AreParticlesAnimatable;

		/// Makes sure the particles are maskable.
		typedef typename StaticAssert<IsBaseOf<Maskable, ParticleType>::RESULT>::Result AreParticlesMaskable;

		/// Makes sure the particles are colorable.
		typedef typename StaticAssert<IsBaseOf<Colorable, ParticleType>::RESULT>::Result AreParticlesColorable;

		/// Makes sure the parent type is at least transformable.
		typedef typename StaticAssert < IsBaseOf<Transformable, Parent>::RESULT || IsSame<Transformable, Parent>::RESULT >::Result IsParentTransformable;

		/// Represents the type that contains the particles.
		typedef typename std::vector<std::pair<PhaseList::const_iterator, Particle<ParticleType> > > ParticleVector;

		/**
		 * De-allocate the memory used by the particles.
		 */
		void clearParticles() {
			for (typename ParticleVector::iterator i = particles.begin();
			     i != particles.end(); ++i) {
				if (i->second.graphic) {
					delete i->second.graphic;
				}
			}
		}

		/**
		 * Finds the first dead particle in the vector of particles.
		 * @return Iterator to the first dead particle found, end iterator if
		 * none were found.
		 */
		typename ParticleVector::iterator findFirstDeadParticle() {
			if (nbParticles >= particles.size()) {
				return particles.end();

			} else {
				bool notFound = true;
				typename ParticleVector::iterator i = particles.begin();

				// We look for the first particle that is dead.
				while (notFound && i != particles.end()) {
					if (i->second.timeLeft <= 0.0) {
						notFound = false;

					} else {
						++i;
					}
				}

				return i;
			}
		}

		void startPhase(typename ParticleVector::iterator particle) {
			if (particle->first != getPhases().end()) {
				particle->second.timeLeft = particle->first->phaseDuration + Random::getRandomDouble(0.0, particle->first->phaseDurationVariance);

				if (!particle->first->animationName.empty()) {
					particle->second.graphic->startAnimation(particle->first->animationName);
				}

				particle->second.alphaCounter = 0.0;
				particle->second.alphaPerSecond = particle->first->alphaPerSecond + Random::getRandomFloat(0.0f, particle->first->alphaPerSecondVariance);
				particle->second.scalingPerSecond = particle->first->scalingPerSecond + Vector2(Random::getRandomFloat(0.0f, particle->first->scalingPerSecondVariance.getX()), Random::getRandomFloat(0.0f, particle->first->scalingPerSecondVariance.getY()));
				particle->second.anglePerSecond = particle->first->anglePerSecond + Random::getRandomFloat(0.0f, particle->first->anglePerSecondVariance);
			}
		}

		/**
		 * Finds an available particle and shoots it.
		 * @return True if there was a particle available to shoot and it was
		 * successfully shot, false if not.
		 */
		bool shootParticle() {
			bool result = false;

			// We make sure the default graphic is valid and that we have at
			// least one phase.
			if (defaultGraphic && !getPhases().empty()) {
				// We try to get a dead particle.
				typename ParticleVector::iterator newParticle = findFirstDeadParticle();

				// If we found a dead particle, we start it.
				if (newParticle != particles.end()) {
					// We make sure the graphic is valid.
					if (!newParticle->second.graphic) {
						newParticle->second.graphic = new ParticleType(*defaultGraphic);
					}

					// We initialize the graphic's properties.
					newParticle->second.graphic->setPosition(this->getPosition());
					Vector2 shootVector(Vector2::UP);
					shootVector.setLength(getShootingForce() + Random::getRandomFloat(0.0f, getShootingForceVariance()));
					shootVector.rotate(getShootingAngle() + Random::getRandomFloat(-getShootingAngleVariance(), getShootingAngleVariance()));
					newParticle->second.graphic->setVelocity(shootVector);
					newParticle->second.graphic->setColor(defaultGraphic->getColor());
					newParticle->second.graphic->setAngle(defaultGraphic->getAngle());
					newParticle->second.graphic->setScaling(defaultGraphic->getScaling());
					newParticle->second.timeLeft = 0.0;

					// We set its first phase.
					newParticle->first = getPhases().begin();

					// We start the phase.
					startPhase(newParticle);

					// If the particle is correctly started, we increment the
					// number of active particles and we return true.
					if (newParticle->second.timeLeft > 0.0) {
						++nbParticles;
						result = true;
					}
				}
			}

			return result;
		}

		/**
		 * Pointer to the default base graphic to use for each particle. Uses
		 * ParticleType's copy constructor to copy from the defaul graphic, so
		 * for particles of derived type, use a different template parameter.
		 * The default graphic is not deleted when the emitter is destroyed, so
		 * you can have multiple emitters with the same default graphic. If it
		 * is set to NULL, the emitter will not emit anything.
		 */
		const ParticleType *defaultGraphic;

		/// Pointer to the emitter's mask.
		Maskable *currentMask;

		/// Used to keep track of the particles' spawning rate.
		double spawningCounter;

		/// Vector containing the particles used to shoot.
		ParticleVector particles;
	};
}

#endif // RB_PARTICLE_EMITTER_H

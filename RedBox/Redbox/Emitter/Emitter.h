/**
 * @file
 * @ingroup Display
 */
#ifndef RB_EMITTER_H
#define RB_EMITTER_H

#include <vector>

#include "IEmitter.h"
#include "ParticleState.h"
#include "Engine.h"
#include "Random.h"

namespace RedBox {
	/**
	 * Represents an emitter. Emitters for specific objects inherit from this
	 * class. The object emitted has to have update() and render() functions
	 * to work properly. This class is abstract.
	 * @ingroup Display
	 */
	template <class T>
	class Emitter: public IEmitter {
	public:
		/**
		 * Default constructor.
		 */
		Emitter(): IEmitter() {
		}
		/**
		 * Copy constructor.
		 * @param src SpriteEmitter to make a copy of.
		 */
		Emitter(const Emitter& src): IEmitter(src), particles(src.particles) {
		}
		/**
		 * Destructor.
		 */
		virtual ~Emitter() {
		}
		/**
		 * Assignation operator overloading.
		 * @param Emitter to make a copy of.
		 * @return Instance of this Emitter.
		 */
		Emitter& operator=(const Emitter& src) {
			IEmitter::operator=(src);
			copyFrom(src);
			return *this;
		}

		/**
		 * Updates the emitter and its particles.
		 */
		virtual void update() {
			// We make sure that the sprite emitter is active and has a valid emitRate.
			if(isActive && emitRate > 0.0 &&
					(nbParticlesToShoot == -1 || nbParticlesToShoot > 0)) {
				float rate = 1.0 / emitRate;
				emitCounter += Engine::getSinceLastUpdate();
				// We try to shoot particles as long as the emission rate lets us.
				while((nbParticlesToShoot == -1 || nbParticlesToShoot > 0) &&
					  emitCounter > rate && shootParticle()) {
					if(nbParticlesToShoot > -1) --nbParticlesToShoot;
					emitCounter -= rate;
				}

				// We check if we have to count the emitter's life span.
				if(lifeSpan != -1.0) {
					// We update the emitter's elapsed time.
					elapsedTime += Engine::getSinceLastUpdate();
					if(lifeSpan < elapsedTime) {
						deactivate();
					}
				}
			}
			// We update the particles that still have a lifespan remaining.
			for(typename std::vector<Particle>::iterator i = particles.begin();
				i != particles.end(); i++) {
				// We check if it is still alive.
				if (i->timeLeft > 0.0) {
					// We update the sprite.
					updateParticle(i->graphicBody);
					// We update the lifespan.
					i->timeLeft -= Engine::getSinceLastUpdate();
				}
				// We update the particles depending on their phase.
				ParticleState::Enum tmpState;
				do {
					tmpState = i->state;
					switch (i->state) {
						case ParticleState::BIRTH:
							updateAlpha(Engine::getSinceLastUpdate() * birthPhase.alphaPerSecond, i->graphicBody);
							updateScaling(Engine::getSinceLastUpdate() * birthPhase.scalingPerSecond, i->graphicBody);
							if(i->timeLeft <= 0.0) {
								i->state = ParticleState::LIFE;
								i->timeLeft = lifePhase.phaseDuration + Random::getRandomDouble(0.0, lifePhase.phaseDurationVariance);
							}
							break;
						case ParticleState::LIFE:
							updateAlpha(Engine::getSinceLastUpdate() * lifePhase.alphaPerSecond, i->graphicBody);
							updateScaling(Engine::getSinceLastUpdate() * lifePhase.scalingPerSecond, i->graphicBody);
							if(i->timeLeft <= 0.0) {
								i->state = ParticleState::DYING;
								i->timeLeft = dyingPhase.phaseDuration + Random::getRandomDouble(0.0, dyingPhase.phaseDurationVariance);
							}
							break;
						case ParticleState::DYING:
							updateAlpha(Engine::getSinceLastUpdate() * dyingPhase.alphaPerSecond, i->graphicBody);
							updateScaling(Engine::getSinceLastUpdate() * dyingPhase.scalingPerSecond, i->graphicBody);
							if(i->timeLeft <= 0.0) {
								i->state = ParticleState::DEAD;
								i->timeLeft = 0.0;
								// We reduce the number of active particles.
								--nbParticles;
							}
							break;
						default:
							break;
					}
				} while(tmpState != i->state);
			}
			deleteIfPossible();
		}
		/**
		 * Renders the emitter and its particles.
		 */
		virtual void render() {
			// We check that the emitter is active before rendering the
			// particles.
			if(isActive) {
				for(typename std::vector<Particle>::iterator i = particles.begin();
					i != particles.end(); i++) {
					if(i->timeLeft > 0.0) {
						renderParticle(i->graphicBody);
					}
				}
			}
		}
		
		
		/**
		 * Gets the maximum number of particles.
		 * @return Maximum number of particles an emitter can have at the
		 * same time.
		 */
		unsigned int getNbMaxParticles() const {
			return particles.size();
		}
		/**
		 * Sets the maximum number of particles.
		 * @param newNbMaxParticles Maximum number of particles the sprite
		 * emitter can have shown at the same time.
		 */
		void setNbMaxParticles(unsigned int newNbMaxParticles) {
			// We make sure to free the memory if we reduce the number of
			// maximum particles.
			if(particles.size() > 0) {
				for(unsigned int i = particles.size() - 1; i >= newNbMaxParticles; i--) {
					if(particles[i].graphicBody) {
						delete particles[i].graphicBody;
					}
				}
			}
			particles.resize(newNbMaxParticles);
		}
	protected:
		/**
		 * Updates the GraphicBody's alpha using the given alpha to add to
		 * the GraphicBody's current alpha value.
		 * @param deltaAlpha Alpha value to add to the GraphicBody's alpha.
		 * @param GraphicBody GraphicBody to have its alpha updated.
		 */
		virtual void updateAlpha(float deltaAlpha, T* GraphicBody)=0;
		/**
		 * Updates the GraphicBody's size using the given scaling value to add
		 * to the GraphicBody's size scaling.
		 * @param deltaScaling Scaling value to add to the GraphicBody's size.
		 * @param GraphicBody GraphicBody to have its size updated.
		 */
		virtual void updateScaling(float deltaScaling, T* GraphicBody)=0;
		/**
		 * Initializes a particle's renerable and returns a pointer to it.
		 * @return Pointer to the created GraphicBody.
		 */
		virtual T* initParticle()=0;
		/**
		 * Starts a particle with the information about its generated angle and
		 * shooting force. If the given pointer to the GraphicBody isn't
		 * initialized, it will initialize it.
		 * @param GraphicBody GraphicBody to have its values initialized to go in
		 * the right direction with the right force.
		 */
		virtual void startParticle(T*& graphicBody)=0;
		/**
		 * Updates the particle. If the pointer recieved is null, the method
		 * will not do anything.
		 * @param GraphicBody Pointer to the GraphicBody to update.
		 */
		virtual void updateParticle(T* graphicBody)=0;
		/**
		 * Renders the particle. If the pointer recieved is null, the method
		 * will not do anything.
		 * @param GraphicBody Pointer to the GraphicBody to render.
		 */
		virtual void renderParticle(T* graphicBody)=0;
	private:
		/**
		 * Represents a particle the sprite emitter will shoot.
		 */
		struct Particle {
			/**
			 * Default constructor.
			 */
			Particle():graphicBody(NULL), timeLeft(0.0), state(ParticleState::DEAD) {
			}
			/**
			 * Parameterized constructor.
			 * @param newSprite Pointer to the graphic used for the particle.
			 * @param newLifespan Time remaining for the sprite to be shown.
			 */
			Particle(T* newGraphicBody, double newTimeLeft,
					 ParticleState::Enum newState):
			graphicBody(newGraphicBody), timeLeft(newTimeLeft),
			state(newState) {
			}
			/**
			 * Copy constructor.
			 * @param src Particle to make a copy of.
			 */
			Particle(const Particle& src) : graphicBody(NULL),
			timeLeft(src.timeLeft), state(src.state) {
				if(src.graphicBody) {
					graphicBody = new T(*src.graphicBody);
				}
			}
			/**
			 * Destructor. Frees up the memory used by the GraphicBody.
			 */
			~Particle() {
				clearGraphicBody();
			}
			/**
			 * Assignation operator overload.
			 * @param src Particle to make a copy of.
			 */
			Particle& operator=(const Particle& src) {
				copyFrom(src);
				return *this;
			}
			/// Pointer to the particle's GraphicBody object.
			T* graphicBody;
			/// Time left in the particle's current phase.
			double timeLeft;
			/// Flag used to know in which phase the particle is.
			ParticleState::Enum state;
		private:
			/**
			 * Frees up all the memory used by the GraphicBody.
			 */
			void clearGraphicBody() {
				if(graphicBody) {
					delete graphicBody;
				}
			}
			/**
			 * Resets the particle.
			 */
			void clean() {
				clearGraphicBody();
				graphicBody = NULL;
				timeLeft = 0.0;
				state = ParticleState::DEAD;
			}
			/**
			 * Makes a copy of the recieved particle.
			 * @param src Particle to make a copy of.
			 */
			void copyFrom(const Particle& src) {
				if(this != &src) {
					if(&src) {
						clearGraphicBody();
						if(src.graphicBody) {
							graphicBody = new T(*src.graphicBody);
						} else {
							graphicBody = NULL;
						}
						timeLeft = src.timeLeft;
						state = src.state;
					} else {
						clean();
					}
				}
			}
		};
		
		/// Vector containing the particles used to shoot.
		std::vector<Particle> particles;
		
		typename std::vector<Particle>::iterator findFirstDeadParticle() {
			if(nbParticles >= particles.size()) {
				return particles.end();
			} else {
				bool notFound = true;
				typename std::vector<Particle>::iterator i = particles.begin();
				// We look for the first particle that is dead.
				while (notFound && i != particles.end()) {
					if (i->state == ParticleState::DEAD) {
						notFound = false;
					} else {
						i++;
					}
				}
				return i;
			}
		}
		
		bool shootParticle() {
			// We try to get a dead particle.
			typename std::vector<Particle>::iterator deadParticle = findFirstDeadParticle();
			// If it's dead, we start it.
			if(deadParticle != particles.end()) {
				startParticle(deadParticle->graphicBody);
				deadParticle->timeLeft = birthPhase.phaseDuration + Random::getRandomDouble(0.0, birthPhase.phaseDurationVariance);
				deadParticle->state = ParticleState::BIRTH;
				++nbParticles;
				return true;
			} else {
				return false;
			}
		}

		void deleteIfPossible() {
			if(nbParticlesToShoot == 0) {
				bool notFound = true;
				typename std::vector<Particle>::iterator i = particles.begin();
				while(notFound && i != particles.end()) {
					if(i->state != ParticleState::DEAD) {
						notFound = false;
					} else {
						++i;
					}
				}
				if(notFound) {
					deactivate();
					if(dieOnDeactivate) {
						this->setToBeDeleted(true);
					}
				}
			}
		}
		
		/**
		 * Resets the emitter.
		 */
		void clean() {
			particles.clear();
		}
		/**
		 * Makes a copy of the recieved emitter.
		 */
		void copyFrom(const Emitter& src) {
			if(this != &src) {
				clean();
				if(&src) {
					particles = src.particles;
				}
			}
		}
	};
}
#endif

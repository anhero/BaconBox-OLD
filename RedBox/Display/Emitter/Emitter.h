/**
 * @file
 * @ingroup Display
 */
#ifndef RB_EMITTER_H
#define RB_EMITTER_H

#include <vector>

#include "IEmitter.h"
#include "ParticleState.h"
#include "RedBoxEngine.h"

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
			if(isActive && emitRate > 0.0) {
				float rate = 1.0 / emitRate;
				emitCounter += RedBoxEngine::getUpdateDelta();
				// We try to shoot particles as long as the emission rate lets us.
				// TODO: initParticle isn't supposed to be used like this and 
				// this code doesn't eve work.
				while(emitCounter > rate && initParticle()) {
					emitCounter -= rate;
				}
				// We check if we have to count the sprite emitter's life span.
				if(lifeSpan != -1.0) {
					// We update the elapsed time for the sprite emitter.
					elapsedTime += RedBoxEngine::getUpdateDelta();
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
					i->renderable->update();
					// We update the lifespan.
					i->timeLeft -= RedBoxEngine::getUpdateDelta();
				}
			}
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
						i->renderable->render();
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
			for(unsigned int i = particles.size() - 1; i >= newNbMaxParticles; i--) {
				if(particles[i].renderable) {
					delete particles[i].renderable;
				}
			}
			particles.resize(newNbMaxParticles);
		}
	protected:
		/**
		 * Updates the renderable's alpha using the given alpha to add to
		 * the renderable's current alpha value.
		 * @param deltaAlpha Alpha value to add to the renderable's alpha.
		 * @param renderable Renderable to have its alpha updated.
		 */
		virtual void updateAlpha(float deltaAlpha, T* renderable)=0;
		/**
		 * Updates the renderable's size using the given scaling value to add
		 * to the renderable's size scaling.
		 * @param deltaScaling Scaling value to add to the renderable's size.
		 * @param renderable Renderable to have its size updated.
		 */
		virtual void updateScaling(float deltaScaling, T* renderable)=0;
		/**
		 * Initializes a particle's renerable and returns a pointer to it.
		 * @return Pointer to the created renderable.
		 */
		virtual T* initParticle()=0;
		/**
		 * Starts a particle with the information about its generated angle and
		 * shooting force. If the given pointer to the renderable isn't
		 * initialized, it will initialize it.
		 * @param renderable Renderable to have its values initialized to go in
		 * the right direction with the right force.
		 */
		virtual void startParticle(T*& renderable)=0;
		/**
		 * Updates the particle. If the pointer recieved is null, the method
		 * will not do anything.
		 * @param renderable Pointer to the renderable to update.
		 */
		virtual void updateParticle(T* renderable)=0;
		/**
		 * Renders the particle. If the pointer recieved is null, the method
		 * will not do anything.
		 * @param renderable Pointer to the renderable to render.
		 */
		virtual void renderParticle(T* renderable)=0;
	private:
		/**
		 * Represents a particle the sprite emitter will shoot.
		 */
		struct Particle {
			/**
			 * Default constructor.
			 */
			Particle():renderable(NULL), timeLeft(0.0), state(ParticleState::DEAD) {
			}
			/**
			 * Parameterized constructor.
			 * @param newSprite Pointer to the graphic used for the particle.
			 * @param newLifespan Time remaining for the sprite to be shown.
			 */
			Particle(T* newRenderable, double newTimeLeft,
					 ParticleState::Enum state):
			renderable(newRenderable), timeLeft(newTimeLeft),
			state(ParticleState::DEAD) {
			}
			/**
			 * Copy constructor.
			 * @param src Particle to make a copy of.
			 */
			Particle(const Particle& src):renderable(src.renderable),
			timeLeft(src.timeLeft), state(src.state) {
				if(renderable) {
					renderable = new T(*renderable);
				}
			}
			/**
			 * Destructor. Frees up the memory used by the renderable.
			 */
			~Particle() {
				clearRenderable();
			}
			/**
			 * Assignation operator overload.
			 * @param src Particle to make a copy of.
			 */
			Particle& operator=(const Particle& src) {
				copyFrom(src);
				return *this;
			}
			/// Pointer to the particle's renderable object.
			T* renderable;
			/// Time left in the particle's current phase.
			double timeLeft;
			/// Flag used to know in which phase the particle is.
			ParticleState::Enum state;
		private:
			/**
			 * Frees up all the memory used by the renderable.
			 */
			void clearRenderable() {
				if(renderable) {
					delete renderable;
				}
			}
			/**
			 * Resets the particle.
			 */
			void clean() {
				clearRenderable();
				renderable = NULL;
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
						clearRenderable();
						renderable = src.renderable;
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
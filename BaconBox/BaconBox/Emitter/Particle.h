/**
 * @file
 */
#ifndef RB_PARTICLE_H
#define RB_PARTICLE_H

#include "BaconBox/Vector2.h"

namespace BaconBox {
	/**
	 * Represents a particle a particle emitter will shoot.
	 * @see BaconBox::ParticleEmitter
	 */
	template <typename T>
	struct Particle {
		/// Pointer to the particle's GraphicBody object.
		T *graphic;

		/// Time left in the particle's current phase.
		double timeLeft;

		/// Counter used for the fading in and out.
		float alphaCounter;

		/// Alpha per second.
		float alphaPerSecond;

		/// Horizontal and vertical scaling per second.
		Vector2 scalingPerSecond;

		/// Rotation angle per second.
		float anglePerSecond;

		/**
		 * Parameterized constructor.
		 * @param newGraphic Pointer to the graphic used for the particle.
		 * @param newTimeLeft Time remaining for the particle.
		 */
		explicit Particle(T *newGraphic = NULL, double newTimeLeft = 0.0) :
			graphic(newGraphic), timeLeft(newTimeLeft), alphaCounter(0.0f),
			alphaPerSecond(0.0f), scalingPerSecond(), anglePerSecond(0.0f) {
		}

		/**
		 * Copy constructor.
		 * @param src Particle to make a copy of.
		 */
		Particle(const Particle &src) : graphic(NULL), timeLeft(src.timeLeft),
			alphaCounter(src.alphaCounter), alphaPerSecond(src.alphaPerSecond),
			scalingPerSecond(src.scalingPerSecond),
			anglePerSecond(src.anglePerSecond) {
		}

		/**
		 * Assignment operator.
		 * @param src Particle to make a copy of.
		 * @return Reference to the modified Particle.
		 */
		Particle &operator=(const Particle &src) {
			if (this != &src) {
				if (graphic) {
					delete graphic;
					graphic = NULL;
				}

				if (src.graphic) {
					graphic = new T(*src.graphic);
				}

				timeLeft = src.timeLeft;
				alphaCounter = src.alphaCounter;
				alphaPerSecond = src.alphaPerSecond;
				scalingPerSecond = src.scalingPerSecond;
				anglePerSecond = src.anglePerSecond;
			}

			return *this;
		}
	};

}

#endif // RB_PARTICLE_H

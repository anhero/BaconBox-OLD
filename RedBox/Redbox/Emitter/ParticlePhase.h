/**
 * @file
 * @ingroup Display
 */
#ifndef RB_PARTICLE_PHASE_H
#define RB_PARTICLE_PHASE_H

#include "Vec2.h"

namespace RedBox {
	/**
	 * Represents a phase in a particle's "life".
	 * @ingroup Display
	 */
	struct ParticlePhase {
		/**
		 * Default constructor.
		 */
		ParticlePhase();

		/**
		 * Parameterized constructor.
		 * @param newPhaseDuration Minimum duration.
		 * @param newPhaseDurationVariance Variance that will be added to the
		 * duration.
		 * @param newAlphaPerSecond Alpha per second to change the particle's
		 * opacity.
		 * @param newScalingPerSecond Scaling per second to change the
		 * particle's size.
		 */
		ParticlePhase(double newPhaseDuration,
					  double newPhaseDurationVariance,
					  float newAlphaPerSecond,
					  const Vec2& newScalingPerSecond);

		/// Minimum duration the phase will last.
		double phaseDuration;

		/// Variance to be added to the duration, between 0 and this value.
		double phaseDurationVariance;

		/// Alpha value being changed per second.
		float alphaPerSecond;

		/// Scaling value being changed per second.
		Vec2 scalingPerSecond;
	};
}
#endif

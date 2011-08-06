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
		 * @param newAnglePerSecond Rotation per second to change the particle's
		 * angle.
		 * @param newAlphaPerSecondVariance Alpha per second variance.
		 * @param newScalingPerSecondVariance Scaling per second variance.
		 * @param newAnglePerSecondVariance Rotation angle per second variance.
		 */
		ParticlePhase(double newPhaseDuration,
					  double newPhaseDurationVariance,
					  float newAlphaPerSecond = 0.0f,
					  const Vec2& newScalingPerSecond = Vec2(),
					  float newAnglePerSecond = 0.0f,
					  float newAlphaPerSecondVariance = 0.0f,
					  const Vec2& newScalingPerSecondVariance = Vec2(),
					  float newAnglePerSecondVariance = 0.0f,
					  const std::string& newAnimationName = std::string());

		/// Minimum duration the phase will last.
		double phaseDuration;

		/// Variance to be added to the duration, between 0 and this value.
		double phaseDurationVariance;

		/// Alpha value being changed per second.
		float alphaPerSecond;

		/// Scaling value being changed per second.
		Vec2 scalingPerSecond;

		/// Rotation angle per second.
		float anglePerSecond;

		/**
		 * Alpha per second variance. A value between 0 and the variance is added
		 * to the alpha per second when a particle is shot.
		 */
		float alphaPerSecondVariance;

		/**
		 * Scaling per second variance. A value between 0 and the variance is
		 * added to the scaling per second when a particle is shot.
		 */
		Vec2 scalingPerSecondVariance;

		/**
		 * Rotation angle per second variance. A value between 0 and the
		 * variance is added to the angle per second when a particle is shot.
		 */
		float anglePerSecondVariance;

		/// Name of the animation to start when the phase begins.
		std::string animationName;
	};
}
#endif

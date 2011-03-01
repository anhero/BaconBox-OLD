/**
 * @file
 * @ingroup Display
 */
#ifndef RB_PARTICLE_STATE_H
#define RB_PARTICLE_STATE_H
namespace RedBox {
	namespace ParticleState {
		/**
		 * Represents at which phase is the particle.
		 * @ingroup Display
		 */
		enum Enum {
			DEAD,
			BIRTH,
			LIFE,
			DYING
		};
	}
}
#endif
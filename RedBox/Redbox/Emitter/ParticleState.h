/**
 * @file
 * @ingroup Display
 */
#ifndef RB_PARTICLE_STATE_H
#define RB_PARTICLE_STATE_H

#include "SafeEnum.h"

namespace RedBox {

	/**
	 * Represents at which phase is the particle.
	 * @ingroup Display
	 */
	struct ParticleStateDef {
		enum type {
			DEAD,
			BIRTH,
			LIFE,
			DYING
		};
	};
	typedef SafeEnum<ParticleStateDef> ParticleState;

}
#endif

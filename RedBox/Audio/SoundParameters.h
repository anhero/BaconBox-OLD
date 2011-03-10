/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUND_PARAMETERS_H
#define RB_SOUND_PARAMETERS_H

#include <string>

#include "PlatformFlagger.h"

namespace RedBox {
	struct SoundParameters {
		/// Name used by the ResourceLoader.
		std::string name;
#ifdef RB_OPENAL
		std::string path;
#endif
	};
}

#endif
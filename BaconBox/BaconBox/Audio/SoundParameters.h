/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_SOUND_PARAMETERS_H
#define RB_SOUND_PARAMETERS_H

#include <string>

#include "PlatformFlagger.h"

namespace BaconBox {
	struct SoundParameters {
		/// Name used by the ResourceManager.
		std::string name;
#if defined(RB_OPENAL) || defined(RB_SDL)
		std::string path;
#endif
	};
}

#endif

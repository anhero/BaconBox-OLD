/**
 * @file
 * @ingroup Audio
 */
 
#ifndef RB_SOUND_INFO_H
#define RB_SOUND_INFO_H

#include "PlatformFlagger.h"

#include <string>

namespace RedBox {
	/**
	 * Contains engine specific information about the sound effect.
	 * @ingroup Audio
	 */
	struct SoundInfo {
		/// Name used by the ResourceManager.
		std::string name;
#ifdef RB_OPENAL
		std::string path;
#endif
	};
}
 
#endif
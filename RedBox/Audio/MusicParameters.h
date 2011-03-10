/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_MUSIC_PARAMETERS_H
#define RB_MUSIC_PARAMETERS_H

#include "PlatformFlagger.h"

#include <string>

namespace RedBox {
	/**
	 * Contains engine specific information about the music.
	 * @ingroup Audio
	 */
	struct MusicParameters {
		/// Name used by the ResourceManager.
		std::string name;
	};
}

#endif
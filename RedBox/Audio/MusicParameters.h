/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_MUSIC_PARAMETERS_H
#define RB_MUSIC_PARAMETERS_H

#include "PlatformFlagger.h"

#ifdef RB_AV_AUDIO_PLAYER
#include <string>
#endif

namespace RedBox {
	/**
	 * Contains engine specific information about the music. Does not contain
	 * the data. Must only contain the information needed to load the music.
	 * For example, a music engine might use it to pass some parameter to load
	 * a sped up version of the music at a given path.
	 * @ingroup Audio
	 */
	struct MusicParameters {
		/// Name used by the ResourceManager.
		std::string name;
#ifdef RB_AV_AUDIO_PLAYER
		/// Path to the music to load.
		std::string filePath;
#endif
	};
}

#endif

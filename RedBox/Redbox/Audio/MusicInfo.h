/**
 * @file
 * @ingroup Audio
 */
 
#ifndef RB_MUSIC_INF0_H
#define RB_MUSIC_INFO_H

#include "PlatformFlagger.h"

#ifdef RB_AV_AUDIO_PLAYER
#include <string>
#endif

namespace RedBox {
	/**
	 * Contains the data about a sound that can be played. Contains platform-
	 * specific data. They must use preprocessors command to set its members.
	 * @ingroup Audio
	 */
	struct MusicInfo {
#ifdef RB_AV_AUDIO_PLAYER
		/// Path to the music file.
		std::string filePath;
#endif
	};
}
 
 #endif

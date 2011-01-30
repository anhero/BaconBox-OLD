/**
 * @file
 * @ingroup Audio
 */
 
#ifndef RB_MUSIC_INF0_H
#define RB_MUSIC_INFO_H

#include <string>

namespace RedBox {
	/**
	 * Contains engine specific information about the music.
	 * @ingroup Audio
	 */
	struct MusicInfo {
		/// Name used by the ResourceLoader.
		std::string name;
	};
}
 
 #endif
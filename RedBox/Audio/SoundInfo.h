/**
 * @file
 * @ingroup Audio
 */
 
#ifndef RB_SOUND_INFO_H
#define RB_SOUND_INFO_H
 
#include <string>

namespace RedBox {
	/**
	 * Contains engine specific information about the sound effect.
	 * @ingroup Audio
	 */
	struct SoundInfo {
		/// Name used by the ResourceLoader.
		std::string name;
	};
}
 
#endif
/**
 * @file
 * @ingroup Audio
 */
 
#ifndef RB_SOUND_INFO_H
#define RB_SOUND_INFO_H

#include "PlatformFlagger.h"

#ifdef RB_OPENAL
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

#include <string>

namespace RedBox {
	/**
	 * Contains the data about a sound that can be played.
	 * @ingroup Audio
	 */
	struct SoundInfo {
#ifdef RB_OPENAL
		/// OpenAL sound buffer ID.
		ALuint bufferId;
#endif
	};
}
 
#endif
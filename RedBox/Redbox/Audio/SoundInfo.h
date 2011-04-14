/**
 * @file
 * @ingroup Audio
 */
 
#ifndef RB_SOUND_INFO_H
#define RB_SOUND_INFO_H

#include "PlatformFlagger.h"

#ifdef RB_OPENAL
#ifdef RB_WIN32
#include <al.h>
#include <alc.h>
#elif defined(RB_LINUX)
#include <AL/al.h>
#include <AL/alc.h>
#else
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
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

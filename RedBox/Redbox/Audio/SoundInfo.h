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
#elif defined(RB_APPLE_PLATFORM)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif
#endif

#ifdef RB_SDL
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
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
#ifdef RB_SDL
		/// Pointer to SDL's sound data.
		Mix_Chunk* data;
#endif
	};
}
 
#endif

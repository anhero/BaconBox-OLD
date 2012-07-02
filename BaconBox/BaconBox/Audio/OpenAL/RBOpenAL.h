/**
 * @file
 * @ingroup Audio
 */
#ifndef RB_OPENAL_H
#define RB_OPENAL_H

#include "BaconBox/PlatformFlagger.h"

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

#endif

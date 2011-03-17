#ifndef RB_PLATFORM_FLAGGER_H
#define RB_PLATFORM_FLAGGER_H

#ifdef LINUX

#define RB_LINUX

#endif // LINUX

#ifdef _WIN32
#include <sdkddkver.h>

#define RB_WIN32

#ifdef _WIN32_WINNT_VISTA
	#define _WIN32_WINNT _WIN32_WINNT_VISTA
#else
	#define _WIN32_WINNT _WIN32_WINNT_WIN2K
#endif // _WIN32_WINNT_VISTA

#endif // _WIN32

#ifdef QT
#define RB_QT
#include "RedBox_global.h"
#endif

#ifdef __APPLE__

#include "TargetConditionals.h"

#define RB_PHYSICS_ENABLED

#define RB_APPLE_PLATFORM
#define RB_OPENGL

#if TARGET_IPHONE_SIMULATOR
	#define RB_IPHONE_PLATFORM
	#define RB_IPHONE_SIMULATOR_PLATFORM
#endif // TARGET_IPHONE_SIMULATOR

#if TARGET_OS_IPHONE
	#define RB_IPHONE_PLATFORM
	#define RB_IPHONE_DEVICE_PLATFORM
#endif // TARGET_OS_IPHONE

#if TARGET_OS_MAC
	#define RB_MAC_PLATFORM
#endif

#if defined(RB_IPHONE_PLATFORM) || defined(RB_MAC_PLATFORM)
	#define RB_OPENAL
	#define RB_AV_AUDIO_PLAYER
	#define RB_SOUND_ENGINE new OpenALEngine()
	#define RB_MUSIC_ENGINE new RBAudioPlayerEngine();
	#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
	#define RB_MUSIC_ENGINE_INCLUDE "RBAudioPlayerEngine.h"
	// Example of the 4 defines needed for the audio engine.
	//#define RB_SOUND_ENGINE new OpenALEngine()
	//#define RB_MUSIC_ENGINE new OpenALEngine()
	//#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
	//#define RB_MUSIC_ENGINE_INCLUDE "OpenALEngine.h"
#endif

#endif // __APPLE__
#endif

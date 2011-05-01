#ifndef RB_PLATFORM_FLAGGER_H
#define RB_PLATFORM_FLAGGER_H

#ifdef QT
	#ifndef RB_QT
		#define RB_QT
	#endif
#endif // QT

#ifdef SDL
	#define RB_SDL
#endif

#ifdef linux
	#define RB_LINUX

	//Use OpenGL on Linux
	#define RB_OPENGL

	#ifdef RB_SDL
		#define RB_SOUND_ENGINE SDLMixerEngine::getInstance()
		#define RB_SOUND_ENGINE_INCLUDE "SDLMixerEngine.h"
		#define RB_MUSIC_ENGINE SDLMixerEngine::getInstance()
		#define RB_MUSIC_ENGINE_INCLUDE "SDLMixerEngine.h"
	#elif defined(RB_QT)
		//TODO: Check: if this is not defined, OpenAL stuff still gets included...
		#define RB_OPENAL
		#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
		#define RB_SOUND_ENGINE new OpenALEngine()
		#define RB_MUSIC_ENGINE NULL
	#endif


	#define	RB_TIME_HELPER_IMPL RedBox::LibcTimeHelper
	#define RB_TIME_HELPER_INCLUDE "LibcTimeHelper.h"
#endif // linux

#ifdef _WIN32
	#ifdef RB_QT
		#include <qt_windows.h>
	//#else
		//#include <sdkddkver.h>
	#endif // RB_QT

	#define RB_WIN32

	#ifdef RB_SDL
		#define RB_SOUND_ENGINE SDLMixerEngine::getInstance()
		#define RB_SOUND_ENGINE_INCLUDE "SDLMixerEngine.h"
		#define RB_MUSIC_ENGINE SDLMixerEngine::getInstance()
		#define RB_MUSIC_ENGINE_INCLUDE "SDLMixerEngine.h"
	#elif defined(RB_QT)
		//TODO: Check: if this is not defined, OpenAL stuff still gets included...
		#define RB_OPENAL
		#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
		#define RB_SOUND_ENGINE new OpenALEngine()
		#define RB_MUSIC_ENGINE NULL
	#endif

	#define RB_OPENGL
	
	#define	RB_TIME_HELPER_IMPL RedBox::WindowsTimeHelper
	#define RB_TIME_HELPER_INCLUDE "WindowsTimeHelper.h"

	/*#ifdef _WIN32_WINNT_VISTA
		#define _WIN32_WINNT _WIN32_WINNT_VISTA
	#else
		#define _WIN32_WINNT _WIN32_WINNT_WIN2K
	#endif // _WIN32_WINNT_VISTA
	*/
#endif // _WIN32

#ifdef __APPLE__

	#include "TargetConditionals.h"

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

	#ifdef RB_MAC_PLATFORM
		#define RB_TIME_HELPER_IMPL RedBox::LibcTimeHelper
		#define RB_TIME_HELPER_INCLUDE "LibcTimeHelper.h"
	#endif

	#ifdef RB_IPHONE_PLATFORM
		#define	RB_TIME_HELPER_IMPL RedBox::IOSTimeHelper
		#define RB_TIME_HELPER_INCLUDE "IOSTimeHelper.h"
	#endif

	#if defined(SDL) && defined(RB_MAC_PLATFORM)
		#define RB_SOUND_ENGINE SDLMixerEngine::getInstance()
		#define RB_SOUND_ENGINE_INCLUDE "SDLMixerEngine.h"
		#define RB_MUSIC_ENGINE SDLMixerEngine::getInstance()
		#define RB_MUSIC_ENGINE_INCLUDE "SDLMixerEngine.h"
	#elif defined(RB_IPHONE_PLATFORM) || defined(RB_MAC_PLATFORM)
		#define RB_OPENAL
		#define RB_AV_AUDIO_PLAYER
		#define RB_SOUND_ENGINE new OpenALEngine()
		#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
		#if defined(RB_QT)
			#define RB_MUSIC_ENGINE NULL
		#else
			#define RB_MUSIC_ENGINE_INCLUDE "RBAudioPlayerEngine.h"
			#define RB_MUSIC_ENGINE new RBAudioPlayerEngine()
		#endif
		// Example of the 4 defines needed for the audio engine.
		//#define RB_SOUND_ENGINE new OpenALEngine()
		//#define RB_MUSIC_ENGINE new OpenALEngine()
		//#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
		//#define RB_MUSIC_ENGINE_INCLUDE "OpenALEngine.h"
	#endif

#endif // __APPLE__

// Defines for input.
#ifdef RB_IPHONE_PLATFORM
	#define RB_POINTER_IMPL new IOSPointer()
	#define RB_POINTER_INCLUDE "IOSPointer.h"
#endif // RB_IPHONE_PLATFORM

#ifdef RB_QT
	#define RB_KEYBOARD_IMPL new QtKeyboard()
	#define RB_KEYBOARD_INCLUDE "QtKeyboard.h"
	#define RB_POINTER_IMPL new QtPointer()
	#define RB_POINTER_INCLUDE "QtPointer.h"
#endif // RB_QT

#ifdef RB_SDL
	#define RB_KEYBOARD_IMPL new SDLKeyboard()
	#define RB_KEYBOARD_INCLUDE "SDLKeyboard.h"
	#define RB_POINTER_IMPL new SDLPointer()
	#define RB_POINTER_INCLUDE "SDLPointer.h"
	#define RB_INPUT_MANAGER_IMPL RedBox::SDLInputManager
	#define RB_INPUT_MANAGER_INCLUDE "SDLInputManager.h"
#endif

#ifndef RB_POINTER_IMPL
	#define RB_POINTER_IMPL NULL
#endif
#ifndef RB_KEYBOARD_IMPL
	#define RB_KEYBOARD_IMPL NULL
#endif
#ifndef RB_ACCELEROMETER_IMPL
	#define RB_ACCELEROMETER_IMPL NULL
#endif
#ifndef RB_GAME_PAD_IMPL
	#define RB_GAME_PAD_IMPL NULL
#endif

#ifndef RB_INPUT_MANAGER_IMPL
	#define RB_INPUT_MANAGER_IMPL RedBox::InputManager
#endif

#endif

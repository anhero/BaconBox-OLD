#ifndef RB_PLATFORM_FLAGGER_H
#define RB_PLATFORM_FLAGGER_H

/* ****************************************************************************
 * Basic platform defines/detection
 */
#ifdef QT
	#ifndef RB_QT
		#define RB_QT
	#endif
#endif // QT

#ifdef SDL
	#define RB_SDL
#endif


/* ****************************************************************************
 * System-specific defines
 */
//Android platform
#ifdef __ANDROID__
#define RB_ANDROID
#endif

//Linux systems
#ifdef linux
	#define RB_LINUX

	#define RB_TIME_HELPER_IMPL RedBox::LibcTimeHelper
	#define RB_TIME_HELPER_INCLUDE "LibcTimeHelper.h"
#ifndef RB_ANDROID
	#define RB_HAS_GCC_STACKTRACE
#endif
#endif // linux

//Windows systems
#ifdef _WIN32
	#ifdef RB_QT
		#include <qt_windows.h>
	#endif // RB_QT

	#define RB_WIN32

	#define RB_TIME_HELPER_IMPL RedBox::WindowsTimeHelper
	#define RB_TIME_HELPER_INCLUDE "WindowsTimeHelper.h"
#endif // _WIN32

//Apple systems
#ifdef __APPLE__
	//Get more informations about the system
	#include "TargetConditionals.h"

	#define RB_APPLE_PLATFORM

	//More detailed platforms
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

	//Time on iOS
	#ifdef RB_IPHONE_PLATFORM
		#define RB_TIME_HELPER_IMPL RedBox::IOSTimeHelper
		#define RB_TIME_HELPER_INCLUDE "IOSTimeHelper.h"
	#elif defined(RB_MAC_PLATFORM)
		// Time on Mac OS X
		#define RB_TIME_HELPER_IMPL RedBox::LibcTimeHelper
		#define RB_TIME_HELPER_INCLUDE "LibcTimeHelper.h"
	#endif

	#define RB_HAS_GCC_STACKTRACE
#endif // __APPLE__

/* ****************************************************************************
 * Platform-specific defines
 */

//SDL platform
#if defined(RB_SDL)
	//Graphics engine for SDL
	#define RB_OPENGL

	//Sound engine for SDL
	#define RB_SOUND_ENGINE SDLMixerEngine::getInstance()
	#define RB_SOUND_ENGINE_INCLUDE "SDLMixerEngine.h"
	#define RB_MUSIC_ENGINE SDLMixerEngine::getInstance()
	#define RB_MUSIC_ENGINE_INCLUDE "SDLMixerEngine.h"

	//Input engine for SDL
	#define RB_KEYBOARD_IMPL new SDLKeyboard()
	#define RB_KEYBOARD_INCLUDE "SDLKeyboard.h"
	#define RB_POINTER_IMPL new SDLPointer()
	#define RB_POINTER_INCLUDE "SDLPointer.h"
	#define RB_INPUT_MANAGER_IMPL RedBox::SDLInputManager
	#define RB_INPUT_MANAGER_INCLUDE "SDLInputManager.h"

	#define RB_MAINWINDOW_IMPL SDLMainWindow::getInstance()
	#define RB_MAINWINDOW_INCLUDE "SDLMainWindow.h"
#endif

//Qt platform
#if defined(RB_QT)
	//Graphics engine for Qt
	#define RB_OPENGL

	//Sound engine for Qt
	#define RB_OPENAL
	#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"
	#define RB_SOUND_ENGINE new OpenALEngine()
	#define RB_MUSIC_ENGINE NULL

	//Input engine for Qt
	#define RB_KEYBOARD_IMPL new QtKeyboard()
	#define RB_KEYBOARD_INCLUDE "QtKeyboard.h"
	#define RB_POINTER_IMPL new QtPointer()
	#define RB_POINTER_INCLUDE "QtPointer.h"

	#define RB_MAINWINDOW_IMPL QtMainWindow::getInstance()
	#define RB_MAINWINDOW_INCLUDE "QtMainWindow.h"
#endif

//iOS platform
#if defined(RB_IPHONE_PLATFORM)
	
	//Sound engine for iOS
	#define RB_OPENAL
	#define RB_AV_AUDIO_PLAYER
	#define RB_SOUND_ENGINE new OpenALEngine()
	#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"

	//Input engine for iOS
	#define RB_POINTER_IMPL new IOSPointer()
	#define RB_POINTER_INCLUDE "IOSPointer.h"
#endif




/*
//Mac platform (without SDL or Qt) (currently unsupported)
//TODO: Support mac platform with cocoa only and related defines
#if defined(RB_MAC_PLATFORM)
	#if defined(RB_QT)
		#define RB_MUSIC_ENGINE NULL
	#else
		#define RB_MUSIC_ENGINE_INCLUDE "RBAudioPlayerEngine.h"
		#define RB_MUSIC_ENGINE new RBAudioPlayerEngine()
	#endif
#endif
*/


/* ****************************************************************************
 * Defaulting implementations if not defined
 */

//For NULL inputs
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

//For NULL sound engine
#ifndef RB_SOUND_ENGINE
	#define RB_SOUND_ENGINE NullAudioEngine::getInstance()
	#define RB_SOUND_ENGINE_INCLUDE "NullAudioEngine.h"
#endif
#ifndef RB_MUSIC_ENGINE
	#define RB_MUSIC_ENGINE NullAudioEngine::getInstance()
	#define RB_MUSIC_ENGINE_INCLUDE "NullAudioEngine.h"
#endif

//Default input manager
#ifndef RB_INPUT_MANAGER_IMPL
	#define RB_INPUT_MANAGER_IMPL RedBox::InputManager
#endif


#endif // RB_PLATFORM_FLAGGER_H

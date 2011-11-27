#ifndef RB_PLATFORM_FLAGGER_H
#define RB_PLATFORM_FLAGGER_H

/*******************************************************************************
 * Basic platform defines/detection
 **************************************************************************** */
#ifdef QT
	#ifndef RB_QT
		#define RB_QT
	#endif
#endif // QT

#ifdef SDL
	#define RB_SDL
#endif


/*******************************************************************************
 * System-specific defines
 ******************************************************************************/
//Android platform
#ifdef __ANDROID__
	#define RB_ANDROID
	#define RB_OPENGLES
#endif // __ANDROID__

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

	#ifdef RB_IPHONE_PLATFORM
        #define RB_OPENGLES
		//Time on iOS
		#define RB_TIME_HELPER_IMPL RedBox::IOSTimeHelper
		#define RB_TIME_HELPER_INCLUDE "IOSTimeHelper.h"
	#elif defined(RB_MAC_PLATFORM)
        #define RB_OPENGL
		// Time on Mac OS X
		#define RB_TIME_HELPER_IMPL RedBox::LibcTimeHelper
		#define RB_TIME_HELPER_INCLUDE "LibcTimeHelper.h"
	#endif

	#define RB_HAS_GCC_STACKTRACE
#endif // __APPLE__

/*******************************************************************************
 * Platform-specific defines
 ******************************************************************************/

//SDL platform
#ifdef RB_SDL
	//Graphics engine for SDL
	#define RB_OPENGL

	//Sound engine for SDL
	#define RB_SOUND_ENGINE_IMPL new SDLMixerEngine()
	#define RB_SOUND_ENGINE_INCLUDE "SDLMixerEngine.h"

	#define RB_MUSIC_ENGINE_IMPL SDLMixerEngine::getInstance()
	#define RB_MUSIC_ENGINE_INCLUDE "SDLMixerEngine.h"

	//Input engine for SDL
	#define RB_KEYBOARD_IMPL new SDLKeyboard()
	#define RB_KEYBOARD_INCLUDE "SDLKeyboard.h"

	#define RB_POINTER_IMPL new SDLPointer()
	#define RB_POINTER_INCLUDE "SDLPointer.h"

	#define RB_INPUT_MANAGER_IMPL RedBox::SDLInputManager
	#define RB_INPUT_MANAGER_INCLUDE "SDLInputManager.h"

	#define RB_MAIN_WINDOW_IMPL new SDLMainWindow()
	#define RB_MAIN_WINDOW_INCLUDE "SDLMainWindow.h"
#endif // RB_SDL

//Qt platform
#ifdef RB_QT
	//Graphics engine for Qt
	#define RB_OPENGL

	//Sound engine for Qt
	#define RB_OPENAL
	#define RB_SOUND_ENGINE_IMPL new OpenALEngine()
	#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"

	//Input engine for Qt
	#define RB_KEYBOARD_IMPL new QtKeyboard()
	#define RB_KEYBOARD_INCLUDE "QtKeyboard.h"

	#define RB_POINTER_IMPL new QtPointer()
	#define RB_POINTER_INCLUDE "QtPointer.h"

	#define RB_MAIN_WINDOW_IMPL new QtMainWindow()
	#define RB_MAIN_WINDOW_INCLUDE "QtMainWindow.h"
#endif // RB_QT

//iOS platform
#ifdef RB_IPHONE_PLATFORM
	//Sound engine for iOS
	#define RB_OPENAL
	#define RB_SOUND_ENGINE_IMPL new OpenALEngine()
	#define RB_SOUND_ENGINE_INCLUDE "OpenALEngine.h"

	//Music engine for iOS
	#define RB_AV_AUDIO_PLAYER
	#define RB_MUSIC_ENGINE_IMPL new RBAudioPlayerEngine()
	#define RB_MUSIC_ENGINE_INCLUDE "RBAudioPlayerEngine.h"


	//Input engine for iOS
	#define RB_POINTER_INCLUDE "IOSPointer.h"
	#define RB_POINTER_IMPL new IOSPointer()

	#define RB_MAIN_WINDOW_IMPL new IOSMainWindow()
	#define RB_MAIN_WINDOW_INCLUDE "IOSMainWindow.h"
#endif // RB_IPHONE_PLATFORM

#if defined (RB_OPENGL) || defined (RB_OPENGLES)
	#define RB_GRAPHIC_DRIVER_IMPL new OpenGLDriver()
	#define RB_GRAPHIC_DRIVER_INCLUDE "OpenGLDriver.h"
#endif

/*
//Mac platform (without SDL or Qt) (currently unsupported)
//TODO: Support mac platform with cocoa only and related defines
#if defined(RB_MAC_PLATFORM)
	#if defined(RB_QT)
		#define RB_MUSIC_ENGINE_IMPL NULL
	#else
		#define RB_MUSIC_ENGINE_INCLUDE "RBAudioPlayerEngine.h"
		#define RB_MUSIC_ENGINE_IMPL new RBAudioPlayerEngine()
	#endif
#endif
*/


/*******************************************************************************
 * Defaulting implementations if not defined
 ******************************************************************************/

// For NULL inputs
#ifndef RB_POINTER_IMPL
	#define RB_POINTER_IMPL new NullPointer()
	#define RB_POINTER_INCLUDE "NullPointer.h"
#endif
#ifndef RB_KEYBOARD_IMPL
	#define RB_KEYBOARD_IMPL new NullKeyboard()
	#define RB_KEYBOARD_INCLUDE "NullKeyboard.h"
#endif
#ifndef RB_ACCELEROMETER_IMPL
	#define RB_ACCELEROMETER_IMPL new NullAccelerometer()
	#define RB_ACCELEROMETER_INCLUDE "NullAccelerometer.h"
#endif
#ifndef RB_GAME_PAD_IMPL
	#define RB_GAME_PAD_IMPL NULL
#endif

// For NULL main window.
#ifndef RB_MAIN_WINDOW_IMPL
	#define RB_MAIN_WINDOW_IMPL new NullMainWindow()
	#define RB_MAIN_WINDOW_INCLUDE "NullMainWindow.h"
#endif

// For NULL sound engine
#ifndef RB_SOUND_ENGINE_IMPL
	#define RB_SOUND_ENGINE_IMPL new NullAudioEngine()
	#define RB_SOUND_ENGINE_INCLUDE "NullAudioEngine.h"
#endif // RB_SOUND_ENGINE_IMPL

// For NULL music engine
#ifndef RB_MUSIC_ENGINE_IMPL
	#define RB_MUSIC_ENGINE_IMPL new NullAudioEngine()
	#define RB_MUSIC_ENGINE_INCLUDE "NullAudioEngine.h"
#endif // RB_MUSIC_ENGINE_IMPL

// For NULL graphic driver.
#ifndef RB_GRAPHIC_DRIVER_IMPL
	#define RB_GRAPHIC_DRIVER_IMPL new NullGraphicDriver()
	#define RB_GRAPHIC_DRIVER_INCLUDE "NullGraphicDriver.h"
#endif

// Default input manager
#ifndef RB_INPUT_MANAGER_IMPL
	#define RB_INPUT_MANAGER_IMPL RedBox::InputManager
#endif

#endif // RB_PLATFORM_FLAGGER_H

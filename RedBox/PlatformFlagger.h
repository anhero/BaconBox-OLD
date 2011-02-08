#ifdef __APPLE__

#include "TargetConditionals.h"

#define RB_APPLE_PLATFORM
#define RB_OPENGL

#ifdef TARGET_IPHONE_SIMULATOR 
	#define RB_IPHONE_PLATFORM
	#define RB_IPHONE_SIMULATOR_PLATFORM
#endif // TARGET_IPHONE_SIMULATOR

#ifdef TARGET_OS_IPHONE
	#define RB_IPHONE_PLATFORM
	#define RB_IPHONE_DEVICE_PLATFORM
#endif // TARGET_OS_IPHONE

#ifdef RB_IPHONE_PLATFORM
	#define RB_SOUND_ENGINE NULL
	#define RB_MUSIC_ENGINE NULL
	// Example of the 4 defines needed for the audio engine.
	//#define RB_SOUND_ENGINE new SoundEngine()
	//#define RB_MUSIC_ENGINE new MusicEngine()
	//#define RB_SOUND_ENGINE_INCLUDE "SoundEngine.h"
	//#define RB_MUSIC_ENGINE_INCLUDE "MusicEngine.h"
#endif

#endif // __APPLE__
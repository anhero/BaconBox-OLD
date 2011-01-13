#ifndef __BACKGROUNDMUSIC_H
#define __BACKGROUNDMUSIC_H

#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	#include "RBIPhoneBackgroundMusic.h"
	#include <Foundation/Foundation.h>
#endif //Target iPhone
#endif //__APPLE__

namespace RedBox {
	
	class BackgroundMusic {
	private:
		
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
		RBIPhoneBackgroundMusic* bgMusic;
#endif //Target iPhone
#endif //__APPLE__
	public:
		
		BackgroundMusic(const char* path);
		void play();
		void playInLoop();
		void playInLoopFor(int nbOfLoop);
		void resume();
		void pause();
		void stop();

	};
}

#endif

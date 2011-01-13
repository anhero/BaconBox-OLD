#ifndef __SOUNDFX_H
#define __SOUNDFX_H

#include <string>

#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
#include "RBIPhoneSound.h"
#endif //Target iPhone
#endif //__APPLE__

namespace RedBox {
	
	class SoundFX {
	private:
		
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
		RBIPhoneSound* aSound;
#endif //Target iPhone
#endif //__APPLE__
	public:
		
		SoundFX(std::string path, const int maxNumberOfInstance);
		void play();
		
	};
}

#endif

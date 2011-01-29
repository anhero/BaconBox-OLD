

#include "SoundFX.h"
#include "ResourceHelper.h"
using namespace RedBox;

SoundFX::SoundFX(std::string path, const int maxNumberOfInstance){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	aSound = [[RBIPhoneSound alloc] initWithPath:[NSString stringWithCString:path.c_str()] maxNumberOfInstance:maxNumberOfInstance];
#endif //Target iPhone
#endif //__APPLE__
	
}

void SoundFX::play(){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[aSound play];
#endif //Target iPhone
#endif //__APPLE__
	
}


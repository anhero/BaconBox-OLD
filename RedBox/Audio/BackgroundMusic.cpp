
#include "BackgroundMusic.h"
using namespace RedBox;


BackgroundMusic::BackgroundMusic(const char* path){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	bgMusic = [[RBIPhoneBackgroundMusic alloc] initWithPath:[NSString stringWithCString:path]];
#endif //Target iPhone
#endif //__APPLE__
}


void BackgroundMusic::play(){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[bgMusic play];
#endif //Target iPhone
#endif //__APPLE__
}

void BackgroundMusic::playInLoop(){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[bgMusic playInLoop];
#endif //Target iPhone
#endif //__APPLE__
}

void BackgroundMusic::playInLoopFor(int nbOfLoop){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[bgMusic playInLoopFor:nbOfLoop];
#endif //Target iPhone
#endif //__APPLE__
}

void BackgroundMusic::resume(){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[bgMusic resume];
#endif //Target iPhone
#endif //__APPLE__
}

void BackgroundMusic::pause(){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[bgMusic pause];
#endif //Target iPhone
#endif //__APPLE__
}

void BackgroundMusic::stop(){
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[bgMusic stop];
#endif //Target iPhone
#endif //__APPLE__
}
#ifndef __IPHONEBACKGROUNDMUSIC_H
#define __IPHONEBACKGROUNDMUSIC_H

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface RBIPhoneBackgroundMusic : NSObject <AVAudioPlayerDelegate> {
	@private
	AVAudioPlayer* BGMusic;
	
	
}
- (id)initWithPath:(NSString *)path;
- (void)play;
- (void)playInLoop;
- (void)playInLoopFor:(int)numberOfLoop;
- (void)resume;
- (void)pause;
- (void)stop;

@end
#endif

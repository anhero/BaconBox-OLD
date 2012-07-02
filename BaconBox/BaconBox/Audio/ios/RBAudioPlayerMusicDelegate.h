#ifndef RB_AV_AUDIO_PLAYER_MUSIC_DELEGATE_H
#define RB_AV_AUDIO_PLAYER_MUSIC_DELEGATE_H

#include "BaconBox/PlatformFlagger.h"

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

typedef enum {
	NOT_FADING,
	FADING_IN_PLAY,
	FADING_IN_RESUME,
	FADING_OUT_STOP,
	FADING_OUT_PAUSE
} FadingState;

#define FADE_TICK_TIME 0.1f

@interface RBAudioPlayerMusicDelegate : NSObject <AVAudioPlayerDelegate> {
	@private
	AVAudioPlayer* BGMusic;
	float fadeDelta;
	float realVolume;
	FadingState fading;
}
- (id)initWithPath:(NSString *)path;
- (void)stopFading;
- (void)play:(int)nbLoops;
- (void)resume;
- (void)pause;
- (void)stop;
- (void)setVolume:(float)newVolume;
- (void)fadeOutStop:(float)time;
- (void)fadeOutStop;
- (void)fadeOutPause:(float)time;
- (void)fadeOutPause;
- (void)fadeInPlay:(int)nbLoops:(float)time;
- (void)fadeInPlay;
- (void)fadeInResume:(float)time;
- (void)fadeInResume;
- (void)refreshVolume;
- (BOOL)isLooping;
- (BOOL)isPaused;
- (BOOL)isStopped;

@end

#endif

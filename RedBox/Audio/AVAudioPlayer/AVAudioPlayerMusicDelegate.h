#ifndef RB_AV_AUDIO_PLAYER_MUSIC_DELEGATE_H
#define RB_AV_AUDIO_PLAYER_MUSIC_DELEGATE_H

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

typedef enum {
	NOT_FADING,
	FADING_IN_PLAY,
	FADING_IN_RESUME,
	FADING_OUT_STOP,
	FADING_OUT_PAUSE
} FadingState;

@interface AVAudioPlayerMusicDelegate : NSObject <AVAudioPlayerDelegate> {
	@private
	AVAudioPlayer* BGMusic;
	float fadeDelta;
	float realVolume;
	FadingState fading;
}
@property (readwrite, assign) float fadeDelta;
- (id)initWithPath:(NSString *)path;
- (void)stopFading;
- (void)play:(int)nbLoops;
- (void)resume;
- (void)pause;
- (void)stop;
- (void)fadeOutStop:(float)time;
- (void)fadeOutStop;
- (void)fadeOutPause:(float)time;
- (void)fadeOutPause;
- (void)fadeInPlay:(int)nbLoops:(float)time;
- (void)fadeInPlay;
- (void)fadeInResume:(float)time;
- (void)fadeInResume;

@end
#endif

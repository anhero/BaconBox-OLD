

#import "AVAudioPlayerMusicDelegate.h"


@implementation AVAudioPlayerMusicDelegate

@synthesize fadeDelta;

- (id)initWithPath:(NSString *)path{
	[super init];

	BGMusic = [[AVAudioPlayer alloc] initWithContentsOfURL:
			   [[NSURL alloc] initFileURLWithPath:path] error:nil];
	BGMusic.delegate = self;

	realVolume = BGMusic.volume;
	
	return self;
	}

- (void)stopFading {
	fading = NOT_FADING;
	BGMusic.volume = realVolume;
}

- (void)play:(int)nbLoops{
	if(!BGMusic.playing) {
		[self stopFading];
		if (nbLoops < -1) {
			nbLoops = -1;
		}
		BGMusic.numberOfLoops = (nbLoops > -1) ? (nbLoops) : (-1);
		BGMusic.volume = realVolume;
		[BGMusic stop];
		[BGMusic play];
	}
}
- (void)resume{
	[self stopFading];
	[BGMusic play];
}
- (void)pause{
	[self stopFading];
	[BGMusic pause];
}
- (void)stop{
	[self stopFading];
	[BGMusic stop];
}

- (void)fadeOutStop:(float)time{
	if(time == 0.0 || BGMusic.volume == 0.0) {
		[self stop];
	} else {
		fading = FADING_OUT_STOP;
		fadeDelta = realVolume / time;
		[self fadeOutStop];
	}
}

- (void)fadeOutStop{
	if(fading == FADING_OUT_STOP) {
		if(BGMusic.volume == 0.0) {
			[self stop];
		} else {
			BGMusic.volume = (BGMusic.volume - fadeDelta < 0.0) ? (0.0) : (BGMusic.volume - fadeDelta);
			[self performSelector:@selector(fadeOutStop) withObject:nil afterDelay: .1];
		}
	}
}

- (void)fadeOutPause:(float)time{
	if(time == 0.0 || BGMusic.volume == 0.0) {
		[self pause];
	} else {
		fading = FADING_OUT_PAUSE;
		fadeDelta = realVolume / time;
		[self fadeOutPause];
	}
}

- (void)fadeOutPause{
	if(fading == FADING_OUT_PAUSE) {
		if(BGMusic.volume == 0.0) {
			[self pause];
		} else {
			BGMusic.volume = (BGMusic.volume - fadeDelta < 0.0) ? (0.0) : (BGMusic.volume - fadeDelta);
			[self performSelector:@selector(fadeOutPause) withObject:nil afterDelay: .1];
		}
	}
}

- (void)fadeInPlay:(int)nbLoops :(float)time {
	if (BGMusic.volume < realVolume || !BGMusic.playing) {
		if(time == 0.0) {
			[self play:nbLoops];
		} else {
			fading = FADING_IN_PLAY;
			if(!BGMusic.playing) {
				BGMusic.volume = 0.0;
				BGMusic.numberOfLoops = (nbLoops > -1) ? (nbLoops) : (-1);
				[BGMusic stop];
				[BGMusic play];
			}
			fadeDelta = realVolume / time;
			[self fadeInPlay];
		}
	}
}

- (void)fadeInPlay {
	if(fading == FADING_IN_PLAY && BGMusic.volume < realVolume) {
		BGMusic.volume = (BGMusic.volume + fadeDelta > realVolume) ? (realVolume) : (BGMusic.volume + fadeDelta);
		[self performSelector:@selector(fadeInResume) withObject:nil afterDelay: .1];
	}
}

- (void)fadeInResume:(float)time{
	if(BGMusic.volume < realVolume || !BGMusic.playing) {
		if(time == 0.0) {
			[self resume];
		} else {
			fading = FADING_IN_RESUME;
			if(!BGMusic.playing) {
				BGMusic.volume = 0.0;
				[BGMusic play];
			}
			fadeDelta = realVolume / time;
			[self fadeInResume];
		}
	}
}

- (void)fadeInResume{
	if(fading == FADING_IN_RESUME && BGMusic.volume < realVolume) {
		BGMusic.volume = (BGMusic.volume + fadeDelta > realVolume) ? (realVolume) : (BGMusic.volume + fadeDelta);
		[self performSelector:@selector(fadeInResume) withObject:nil afterDelay: .1];
	}
}

#pragma mark BGMusic delegate methode


- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player{
	[self pause];
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player{
	[self resume];
}


@end

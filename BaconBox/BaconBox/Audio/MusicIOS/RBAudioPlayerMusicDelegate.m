#import "RBAudioPlayerMusicDelegate.h"

#include "PlatformFlagger.h"

#include "MusicEngine.h"
#include "Sound.h"

@implementation RBAudioPlayerMusicDelegate

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
	BGMusic.volume = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)));
}

- (void)play:(int)nbLoops{
	if(!BGMusic.playing) {
		[self stopFading];
		if (nbLoops < -1) {
			nbLoops = -1;
		}
		BGMusic.numberOfLoops = (nbLoops > -1) ? (nbLoops) : (-1);
		BGMusic.volume = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)));
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

- (void)setVolume:(float)newVolume {
	realVolume = newVolume;
}

- (void)fadeOutStop:(float)time{
	if(time == 0.0 || BGMusic.volume == 0.0) {
		[self stop];
	} else {
		fading = FADING_OUT_STOP;
		fadeDelta = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME))) / (time / FADE_TICK_TIME);
		[self fadeOutStop];
	}
}

- (void)fadeOutStop{
	if(fading == FADING_OUT_STOP) {
		if(BGMusic.volume == 0.0) {
			[self stop];
		} else {
			BGMusic.volume = (BGMusic.volume - fadeDelta < 0.0) ? (0.0) : (BGMusic.volume - fadeDelta);
			[self performSelector:@selector(fadeOutStop) withObject:nil afterDelay: FADE_TICK_TIME];
		}
	}
}

- (void)fadeOutPause:(float)time{
	if(time == 0.0 || BGMusic.volume == 0.0) {
		[self pause];
	} else {
		fading = FADING_OUT_PAUSE;
		fadeDelta = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME))) / (time / FADE_TICK_TIME);
		[self fadeOutPause];
	}
}

- (void)fadeOutPause{
	if(fading == FADING_OUT_PAUSE) {
		if(BGMusic.volume == 0.0) {
			[self pause];
		} else {
			BGMusic.volume = (BGMusic.volume - fadeDelta < 0.0) ? (0.0) : (BGMusic.volume - fadeDelta);
			[self performSelector:@selector(fadeOutPause) withObject:nil afterDelay: FADE_TICK_TIME];
		}
	}
}

- (void)fadeInPlay:(int)nbLoops :(float)time {
	if (BGMusic.volume < (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME))) || !BGMusic.playing) {
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
			fadeDelta = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume())) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)) / (time / FADE_TICK_TIME);
			[self fadeInPlay];
		}
	}
}

- (void)fadeInPlay {
	if(fading == FADING_IN_PLAY && BGMusic.volume < (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)))) {
		BGMusic.volume = (BGMusic.volume + fadeDelta > (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume())))) ? ((realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)))) : (BGMusic.volume + fadeDelta);
		[self performSelector:@selector(fadeInPlay) withObject:nil afterDelay: FADE_TICK_TIME];
	}
}

- (void)fadeInResume:(float)time{
	if(BGMusic.volume < (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME))) || !BGMusic.playing) {
		if(time == 0.0) {
			[self resume];
		} else {
			fading = FADING_IN_RESUME;
			if(!BGMusic.playing) {
				BGMusic.volume = 0.0;
				[BGMusic play];
			}
			fadeDelta = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME))) / (time / FADE_TICK_TIME);
			[self fadeInResume];
		}
	}
}

- (void)fadeInResume{
	if(fading == FADING_IN_RESUME && BGMusic.volume < (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)))) {
		BGMusic.volume = (BGMusic.volume + fadeDelta > (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume())))) ? ((realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)))) : (BGMusic.volume + fadeDelta);
		[self performSelector:@selector(fadeInResume) withObject:nil afterDelay: FADE_TICK_TIME];
	}
}

- (void)refreshVolume {
	BGMusic.volume = (realVolume * (static_cast<float>(BaconBox::AudioEngine::getMusicEngine().getMusicVolume()) / static_cast<float>(BaconBox::Sound::MAX_VOLUME)));
}

- (BOOL)isLooping{
	return BGMusic.numberOfLoops == -1;
}

- (BOOL)isPaused{
	return !BGMusic.playing && BGMusic.currentTime != 0.0;
}

- (BOOL)isStopped{
	return !BGMusic.playing && BGMusic.currentTime == 0.0;
}

#pragma mark BGMusic delegate methode

- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player{
	[self pause];
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player{
	[self resume];
}

@end

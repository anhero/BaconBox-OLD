

#import "RBIPhoneBackgroundMusic.h"


@implementation RBIPhoneBackgroundMusic



- (id)initWithPath:(NSString *)path{
	[super init];

	BGMusic = [[AVAudioPlayer alloc] initWithContentsOfURL:
			   [[NSURL alloc] initFileURLWithPath:path] error:nil];
	BGMusic.delegate = self;

	
	return self;
	}

- (void)play{
	BGMusic.numberOfLoops = 0;
	[BGMusic stop];
	[BGMusic play];
}
- (void)playInLoop{
	BGMusic.numberOfLoops = -1;
	[BGMusic stop];
	[BGMusic play];
}
- (void)playInLoopFor:(int)numberOfLoop{
		BGMusic.numberOfLoops = (numberOfLoop > 1? numberOfLoop-1 : 0);
	[BGMusic stop];
	[BGMusic play];
}
- (void)resume{
	[BGMusic play];
}
- (void)pause{
[BGMusic pause];
}
- (void)stop{
	[BGMusic stop];
}



#pragma mark BGMusic delegate methode


- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player{
	[self pause];
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player{
	[self resume];
}


@end

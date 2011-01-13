#import "RBIPhoneSound.h"


@implementation RBIPhoneSound

- (id)initWithPath:(NSString*)path maxNumberOfInstance:(int)maxNbInstance{
	[super init];
	aSound = [[RevolverSound alloc] initWithFile:path rounds:maxNbInstance];
	return self;
}
- (void)play{
	[aSound play];
	
}

@end

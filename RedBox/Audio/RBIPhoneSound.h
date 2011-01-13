#ifndef __RBIPHONESOUND_H
#define __RBIPHONESOUND_H


#import <Foundation/Foundation.h>
#import "Finch.h"
#import "Sound.h"
#import "RevolverSound.h"


@interface RBIPhoneSound : NSObject {
	RevolverSound* aSound;
	
}
- (id)initWithPath:(NSString*)path maxNumberOfInstance:(int)maxNbInstance;
- (void)play;

@end
#endif

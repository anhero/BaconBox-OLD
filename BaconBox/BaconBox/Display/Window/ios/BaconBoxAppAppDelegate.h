#import <UIKit/UIKit.h>

@class BaconBoxAppViewController;

@interface BaconBoxAppAppDelegate : NSObject <UIApplicationDelegate> {
@private

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet BaconBoxAppViewController *viewController;


+ (void)setViewController:(BaconBoxAppViewController*) controller;

@end

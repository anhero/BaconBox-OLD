#import <UIKit/UIKit.h>

@class RedBoxAppViewController;

@interface RedBoxAppAppDelegate : NSObject <UIApplicationDelegate> {
@private

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet RedBoxAppViewController *viewController;

@end

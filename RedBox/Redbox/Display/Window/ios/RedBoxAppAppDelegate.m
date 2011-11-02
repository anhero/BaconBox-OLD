#import "RedBoxAppAppDelegate.h"

#import "EAGLView.h"

#import "RedBoxAppViewController.h"
#include <RedBox.h>
#include <RedBox/GraphicDriver.h>
#include "MainWindow.h"
static RedBoxAppViewController *redBoxViewController = nil;

@implementation RedBoxAppAppDelegate


@synthesize window;

@synthesize viewController;

+ (void)setViewController:(RedBoxAppViewController*) controller {
    redBoxViewController = controller;
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    if(redBoxViewController == nil){
        redBoxViewController = [[[RedBoxAppViewController alloc] initWithFrame:screenBounds] autorelease];
    }
    
    self.window = [[[UIWindow alloc] initWithFrame: screenBounds] autorelease];
    self.viewController = redBoxViewController;
    self.window.rootViewController = self.viewController;
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
    //RedBox::GraphicDriver::getInstance().initializeGraphicDriver(RedBox::MainWindow::getInstance().getResolutionWidth(), RedBox::MainWindow::getInstance().getResolutionHeight());
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	/*
	 Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	 Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
	 */
	[self.viewController stopAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	// Save data if appropriate.
	[self.viewController stopAnimation];
}

- (void)dealloc {

	[window release];
	[viewController release];
    [super dealloc];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	[self.viewController startAnimation];
}

@end

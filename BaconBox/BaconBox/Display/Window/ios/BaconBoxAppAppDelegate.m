#import "BaconBoxAppAppDelegate.h"

#import "EAGLView.h"

#import "BaconBoxAppViewController.h"
#include <BaconBox.h>
#include <BaconBox/GraphicDriver.h>
#include "MainWindow.h"
static BaconBoxAppViewController *baconBoxViewController = nil;

@implementation BaconBoxAppAppDelegate


@synthesize window;

@synthesize viewController;

+ (void)setViewController:(BaconBoxAppViewController*) controller {
    baconBoxViewController = controller;
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    if(baconBoxViewController == nil){
        baconBoxViewController = [[[BaconBoxAppViewController alloc] initWithFrame:screenBounds] autorelease];
    }
    
    self.window = [[[UIWindow alloc] initWithFrame: screenBounds] autorelease];
    self.viewController = baconBoxViewController;
    self.window.rootViewController = self.viewController;
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
    //BaconBox::GraphicDriver::getInstance().initializeGraphicDriver(BaconBox::MainWindow::getInstance().getResolutionWidth(), BaconBox::MainWindow::getInstance().getResolutionHeight());
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

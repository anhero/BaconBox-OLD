#include "ResourcePathHandler.h"

#include "PlatformFlagger.h"
#ifdef RB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

using namespace RedBox;

std::string ResourcePathHandler::getResourcePathFor(const std::string& item) {
	std::string path;
#ifdef RB_IPHONE_PLATFORM
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSString *resourceDirectory = [[NSBundle mainBundle] resourcePath];
	path = ((std::string)[resourceDirectory cStringUsingEncoding:NSASCIIStringEncoding] + "/" + item );
	[pool release];
#endif
	return path;
}

std::string ResourcePathHandler::getDocumentPathFor(const std::string& item) {
	std::string documentPath = getDocumentPath();
	documentPath +=  "/" + item;
	return documentPath;
}

std::string ResourcePathHandler::getDocumentPath() {
	std::string documentPath;
#ifdef RB_IPHONE_PLATFORM
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	documentPath = [documentsDirectory cStringUsingEncoding:NSASCIIStringEncoding];
	[pool release];
#endif
	return documentPath;		
}

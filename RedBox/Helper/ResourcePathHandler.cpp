#include "ResourcePathHandler.h"

using namespace RedBox;

std::string ResourcePathHandler::getResourcePathFor(const std::string& item) {
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSString *resourceDirectory = [[NSBundle mainBundle] resourcePath];
	std::string path = ((std::string)[resourceDirectory cStringUsingEncoding:NSASCIIStringEncoding] + "/" + item );
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
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	documentPath = [documentsDirectory cStringUsingEncoding:NSASCIIStringEncoding];
	[pool release];
	
#endif
	return documentPath;		
}

#include "ResourcePathHandler.h"

#include "PlatformFlagger.h"
#ifdef RB_IPHONE_PLATFORM
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

#if defined(RB_QT)
#include <QDir>
#include <iostream>
#include <QCoreApplication>
#include <QDesktopServices>
#endif
#include "RedBoxEngine.h"
using namespace RedBox;


std::string ResourcePathHandler::getResourcePathFor(const std::string& item) {
	std::string path;
#ifdef RB_IPHONE_PLATFORM
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSString *resourceDirectory = [[NSBundle mainBundle] resourcePath];
	path = ((std::string)[resourceDirectory cStringUsingEncoding:NSASCIIStringEncoding] + "/" + item );
	[pool release];
#else
	
	path = RedBoxEngine::applicationPath;
	
#ifdef RB_MAC_PLATFORM
	path = path + "/../Resources/" + item;
#else
	path = path + "/resources/" + item;
#endif

#endif
	return path;
}

std::string ResourcePathHandler::getDocumentPathFor(const std::string& item) {
	std::string documentPath = getDocumentPath();
	documentPath +=  "/" + item;
	return documentPath;
}

std::string ResourcePathHandler::getDocumentPath() {
#ifdef RB_IPHONE_PLATFORM
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
	std::string documentPath = [documentsDirectory cStringUsingEncoding:NSASCIIStringEncoding];
	[pool release];
	return documentPath;
#elif defined(RB_QT)
	return QDesktopServices::storageLocation(QDesktopServices::DataLocation).toStdString();
#endif
}

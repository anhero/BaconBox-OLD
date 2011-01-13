//RESOURCE_PATH_FOR() macro function
//Iphone
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
//DEPRECATED MACRO, USE getResourcePathFor() INSTEAD!!!
#define RESOURCE_PATH_FOR(path) (char*)((std::string)[[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSASCIIStringEncoding] + "/" + path ).c_str()
#endif

#ifndef __RESOURCEPATHANDLER_H
#define __RESOURCEPATHANDLER_H

#include <string>

namespace RedBox {
	
	class ResourcePathHandler {
		
	public:
		static std::string getResourcePathFor(const std::string& item){
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			
			NSString *resourceDirectory = [[NSBundle mainBundle] resourcePath];
			std::string path = ((std::string)[resourceDirectory cStringUsingEncoding:NSASCIIStringEncoding] + "/" + item );
			[pool release];
#endif
			return path;
		}
		static std::string getDocumentPathFor(const std::string& item){
			std::string documentPath = getDocumentPath();
			documentPath +=  "/" + item;
			return documentPath;
		}
		static std::string getDocumentPath(){
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
	};
}

#endif
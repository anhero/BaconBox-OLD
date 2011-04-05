/**
 * @file
 * @ingroup Helper
 */

//RESOURCE_PATH_FOR() macro function
//Iphone
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
//DEPRECATED MACRO, USE getResourcePathFor() INSTEAD!!!
#define RESOURCE_PATH_FOR(path) (char*)((std::string)[[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSASCIIStringEncoding] + "/" + path ).c_str()
#endif

#ifndef RB_RESOURCE_PATH_HANDLER_H
#define RB_RESOURCE_PATH_HANDLER_H

#include <string>

namespace RedBox {
	/**
	 * Functions used to get the resource paths for files.
	 * @ingroup Helper
	 */
	class ResourcePathHandler {
	public:
		/**
		 * Gets the resource path for a file name.
		 * @return Full resource path for the file.
		 */
		static std::string getResourcePathFor(const std::string& item);
		/**
		 * Gets the document path for a file name.
		 * @return Full document path for the file.
		 */
		static std::string getDocumentPathFor(const std::string& item);
		/**
		 * Gets the document path.
		 * @return Full document path.
		 */
		static std::string getDocumentPath();
	private:
		/**
		 * Default constructor, to make sure no one tries to instantiate this
		 * class.
		 */
		ResourcePathHandler();
	};
}

#endif

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
namespace BaconBox {
	/**
	 * Functions used to get the resource paths for files. All slashes must be
	 * forward slashes. Backslashes are not treated as folder separators.
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

		/**
		 * Creates the folder hierarchy in the document folder.
		 * @param path Path of folders to create.
		 */
		static bool createDocumentFolder(const std::string &path);

		/**
		 * Creates a folder at the specified path. Prints a message in the
		 * console and returns true if there was an error creating the folder.
		 * If the folder to create already exists, it is not considered as an
		 * error.
		 * @param path Absolute path of the folder to create.
		 * @return True if an error occurred, false if not.
		 */
		static bool createFolder(const std::string &path);

		/**
		 * Creates the folder hierarchy from the path.
		 * @param path Path of the folders to create.
		 * @return True if an error occurred, false if not.
		 */
		static bool createFolderTree(const std::string &path);

		/**
		 * Checks if a folder already exists.
		 * @param path Path to the folder to check.
		 * @return True if it exists, false if not.
		 */
		static bool folderExists(const std::string &path);

		/**
		 * Checks wether or not a file exists and is readable.
		 * @param filePath Path to the file to check its readability.
		 * @return True if the file exists and is readable, false if not.
		 */
		static bool isFileReadable(const std::string &filePath);

		/**
		 * Checks wether or not a file exists and is writable.
		 * @param filePath Path to the file to check its writability.
		 * @return True if the file exists and is writable, false if not.
		 */
		static bool isFileWritable(const std::string &filePath);
	private:
		/**
		 * Default constructor, to make sure no one tries to instantiate this
		 * class.
		 */
		ResourcePathHandler();
		
	
	};
}

#endif

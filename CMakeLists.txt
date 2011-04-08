cmake_minimum_required(VERSION 2.6)
project(RedBox)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BUILD_TYPE}/lib/)


set(CMAKE_MODULE_PATH "${RedBox_SOURCE_DIR}/CMake/module/")
include(Function)
#include("${RedBox_SOURCE_DIR}/CMake/module/Function.cmake")

recurseFolderList(RedBox_header_search_path ${RedBox_SOURCE_DIR}/RedBox)


#if(APPLE)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
#mm(CMAKE_CXX_FLAGS)
#endif(APPLE)

	
find_package(OpenGL)
#list(APPEND RedBox_linkDir_list ${OpenGL_LIBRARY_DIRS})
#list(APPEND RedBox_IncludeDir_list ${OpenGL_INCLUDE_DIR})
#list(APPEND RedBox_libraries_list ${OpenGL_LIBRARIES})

if(IPHONE)
set(RedBox_framework_list  "Foundation" )#"AudioToolBox" "AVFoundation" "CoreGraphics" "OpenAL" "QuartzCore" "UIKit")
	foreach(framework ${RedBox_framework_list})
		findpkg_framework(${framework})		
		list(APPEND RedBox_IncludeDir_list ${${framework}_FRAMEWORK_INCLUDES})
		list(APPEND RedBox_libraries_list ${${framework}_LIBRARY_FWK})
	endforeach(framework)
endif(IPHONE)

#Headers search path
include_directories(${RedBox_header_search_path})
include_directories("${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/include/")
#include_directories(${OpenGL_INCLUDE_DIR})

include_directories(${RedBox_IncludeDir_list})




#libraries search path
link_directories(${CMAKE_BUILD_TYPE}/lib/)
link_directories(${CMAKE_BUILD_TYPE}/Dependencies/lib/)


copy(${RedBox_SOURCE_DIR}/libraries/ios/universal/lib ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/lib/)
copy(${RedBox_SOURCE_DIR}/libraries/ios/universal/include ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/include/)


set(RedBox_Compile_Static 1 CACHE bool "Compile RedBox as a static lib")
set(RedBox_Compile_Static 0 CACHE bool "Compile RedBox as a shared lib")



#We add the static and shared library depending on the case
file(GLOB_RECURSE source_files RedBox/*)
if(${RedBox_Compile_Static})
	add_library(RedBox STATIC ${source_files})
	target_link_libraries(
	RedBox
	png
	freetype
	vorbisdec
	RedBox_libraries_list
)
endif(${RedBox_Compile_Static})

if(${RedBox_Compile_Shared})
	add_library(RedBoxShared SHARED ${source_files})
	target_link_libraries(
	RedBoxShared
	png
	freetype
	vorbisdec
	RedBox_libraries_list
)
endif(${RedBox_Compile_Shared})

install(TARGETS RedBox DESTINATION /Users/dupuisj/Desktop/libfuckyeah)


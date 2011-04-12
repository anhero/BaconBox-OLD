cmake_minimum_required(VERSION 2.6)
project(RedBox)
set(LIBRARY_OUTPUT_PATH  ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/)

set(CMAKE_MODULE_PATH "${RedBox_SOURCE_DIR}/script/CMake/module/")
include(Function)
include(${RedBox_SOURCE_DIR}/RedBox/Sources.cmake)

recurseFolderList(RedBox_header_search_path ${RedBox_SOURCE_DIR}/RedBox)



if(iphone)
set(RedBox_framework_list  "Foundation" "AudioToolBox" "AVFoundation" "CoreGraphics" "OpenAL" "QuartzCore" "UIKit" "OpenGLES")
	foreach(framework ${RedBox_framework_list})
		findpkg_framework(${framework})		
		list(APPEND RedBox_IncludeDir_list ${${framework}_FRAMEWORK_INCLUDES})
		list(APPEND RedBox_libraries_list ${${framework}_LIBRARY_FWK})
	endforeach(framework)

else()
  		set(QT_USE_QTOPENGL TRUE)   
		set(QT 1)	
		ADD_DEFINITIONS("-DQT")
		FIND_PACKAGE( Qt4 REQUIRED)	
		INCLUDE( ${QT_USE_FILE} )

		list(APPEND RedBox_IncludeDir_list ${QT_INCLUDE_DIR} ${QT_QTOPENGL_INCLUDE_DIR})
		list(APPEND RedBox_libraries_list ${QT_LIBRARIES})
		set(CFLAGS "-m32" ${CFLAGS})
		set(CXXFLAGS "-m32" ${CXXFLAGS})
endif(iphone)


#Headers search path
include_directories(${RedBox_header_search_path})
include_directories("${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/include/")
include_directories(${RedBox_IncludeDir_list})


#libraries search path
link_directories( ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/)
link_directories( ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/lib/)

#we build dependencies with libbuildtool (only if needed)
if(iphone)
	if(NOT IS_DIRECTORY ${RedBox_SOURCE_DIR}/libraries/ios/universal)
		execute_process(COMMAND	${RedBox_SOURCE_DIR}/script/libbuildtool/iphone-universal)
	endif(NOT IS_DIRECTORY ${RedBox_SOURCE_DIR}/libraries/ios/universal)
else()
	if(NOT IS_DIRECTORY ${RedBox_SOURCE_DIR}/libraries/current)
	message(STATUS "${RedBox_SOURCE_DIR}/script/libbuildtool/current")
		execute_process(COMMAND	${RedBox_SOURCE_DIR}/script/libbuildtool/current)
	endif(NOT IS_DIRECTORY ${RedBox_SOURCE_DIR}/libraries/current)
endif(iphone)



#we copy the header private and public header files
file(MAKE_DIRECTORY ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include/RedBox)
configure_file(${Public_RedBox_Headers} ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include COPYONLY)
foreach(privateHeader ${Private_RedBox_Headers})
	configure_file(${privateHeader} ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include/RedBox COPYONLY)
endforeach(privateHeader ${Private_RedBox_Headers})


#we copy the depencies in the right place 
if(iphone)
	copy(${RedBox_SOURCE_DIR}/libraries/ios/universal/lib ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/lib/)
	copy(${RedBox_SOURCE_DIR}/libraries/ios/universal/include ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/include/)
else()
	copy(${RedBox_SOURCE_DIR}/libraries/current/lib ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/lib/)
	copy(${RedBox_SOURCE_DIR}/libraries/current/include ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Dependencies/include/)
endif(iphone)

#Seting switch for static and shared compilation
set(RedBox_Compile_Static 1 CACHE bool "Compile RedBox as a static lib")
set(RedBox_Compile_Static 0 CACHE bool "Compile RedBox as a shared lib")

#mm(RedBoxHeaders)

#We add the static and shared library depending on the case
if(${RedBox_Compile_Static})
	add_library(RedBox STATIC ${RedBoxSources} ${RedBoxHeaders})
	target_link_libraries(
	RedBox
	png
	freetype
	vorbisdec
	RedBox_libraries_list
)
endif(${RedBox_Compile_Static})

if(${RedBox_Compile_Shared})
	add_library(RedBoxShared SHARED ${RedBoxSources} ${RedBoxHeaders})
	target_link_libraries(
	RedBoxShared
	png
	freetype
	vorbisdec
	RedBox_libraries_list
)
endif(${RedBox_Compile_Shared})

#Installation
#install(TARGETS RedBox DESTINATION )



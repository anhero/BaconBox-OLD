cmake_minimum_required(VERSION 2.6)
project(RedBox)

# Default build is SDL. If none set, set SDL
if(NOT iphone AND NOT QT AND NOT SDL)
	set(SDL 1)
endif(NOT iphone AND NOT QT AND NOT SDL)

#We force the build type to be at least debug
if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

#Define the DEBUG symbol if necessary.
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	ADD_DEFINITIONS("-DDEBUG")
	if(NOT WIN32)
		set(CMAKE_CXX_FLAGS_DEBUG "-g -rdynamic")
	endif(NOT WIN32)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

if("${CMAKE_GENERATOR}" STREQUAL "Xcode")
	set(LIBRARY_OUTPUT_PATH  ${RedBox_BINARY_DIR}/lib/)
else()
	set(LIBRARY_OUTPUT_PATH  ${RedBox_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
endif("${CMAKE_GENERATOR}" STREQUAL "Xcode")

set(CMAKE_MODULE_PATH "${RedBox_SOURCE_DIR}/script/CMake/module/")
include(Function)

recurseFolderList(RedBox_header_search_path ${RedBox_SOURCE_DIR}/RedBox)

if(iphone)
	set(RedBox_framework_list  "Foundation" "AudioToolBox" "AVFoundation" "CoreGraphics" "OpenAL" "QuartzCore" "UIKit" "OpenGLES")
	foreach(framework ${RedBox_framework_list})
		findpkg_framework(${framework})		
		list(APPEND RedBox_IncludeDir_list ${${framework}_FRAMEWORK_INCLUDES})
		list(APPEND RedBox_libraries_list ${${framework}_LIBRARY_FWK})
	endforeach(framework)
	include(${RedBox_SOURCE_DIR}/RedBox/Sources.cmake)

elseif(ANDROID)
	#TODO
elseif(QT)
	set(QT_USE_QTOPENGL TRUE)   
	set(QT 1)	
	ADD_DEFINITIONS("-DRB_QT")
	ADD_DEFINITIONS("-DQT")

	include(${RedBox_SOURCE_DIR}/RedBox/Sources.cmake)
	
	FIND_PACKAGE( Qt4 REQUIRED)	
	INCLUDE( ${QT_USE_FILE} )

	qt4_wrap_cpp(RedBox_QT_MOC_sources ${RedBox_QT_MOC_headers})
	  
	INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

	FIND_PACKAGE(OpenAL REQUIRED)
	list(APPEND RedBox_IncludeDir_list ${OPENAL_INCLUDE_DIR})
	list(APPEND RedBox_libraries_list ${OPENAL_LIBRARY})

	list(APPEND RedBoxSources ${RedBox_QT_MOC_sources})

	list(APPEND RedBox_IncludeDir_list ${QT_INCLUDE_DIR} ${QT_QTOPENGL_INCLUDE_DIR})
	list(APPEND RedBox_libraries_list ${QT_LIBRARIES})
else(iphone)
	MESSAGE(STATUS "Building with SDL.")
	ADD_DEFINITIONS("-DSDL")

	include(${RedBox_SOURCE_DIR}/RedBox/Sources.cmake)
	INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )

	#pthreads seems to be only needed on Linux for SDL.
	if("${CMAKE_SYSTEM}" MATCHES "Linux")
		find_package (Threads)
		list(APPEND RedBox_libraries_list ${CMAKE_THREAD_LIBS_INIT})
	endif("${CMAKE_SYSTEM}" MATCHES "Linux")
	
	FIND_PACKAGE(OpenGL REQUIRED)
	list(APPEND RedBox_IncludeDir_list ${OPENGL_INCLUDE_DIR})
	list(APPEND RedBox_libraries_list ${OPENLGL_LIBRARY})
	if(WIN32)
		list(APPEND RedBox_libraries_list mingw32 m user32 gdi32 winmm imm32 ole32 oleaut32 version uuid)
	endif(WIN32)
	list(APPEND RedBox_libraries_list SDL_mixer)
	#TODO: Have an option to allow or disallow vorbis...
	list(APPEND RedBox_libraries_list vorbisenc)
	list(APPEND RedBox_libraries_list vorbisfile)
	list(APPEND RedBox_libraries_list vorbis)
	list(APPEND RedBox_libraries_list ogg)
	list(APPEND RedBox_libraries_list SDL)
endif(iphone)



#Headers search path
include_directories(${RedBox_header_search_path})
include_directories("${RedBox_BINARY_DIR}/Dependencies/include/")
include_directories(${RedBox_IncludeDir_list})


#libraries search path
link_directories( ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib/)

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





#we copy the depencies in the right place 
if(iphone)
	copy(${RedBox_SOURCE_DIR}/libraries/ios/universal/lib ${RedBox_BINARY_DIR}/Dependencies/lib/)
	copy(${RedBox_SOURCE_DIR}/libraries/ios/universal/include ${RedBox_BINARY_DIR}/Dependencies/include/)
else()
	copy(${RedBox_SOURCE_DIR}/libraries/current/lib ${RedBox_BINARY_DIR}/Dependencies/lib/)
	copy(${RedBox_SOURCE_DIR}/libraries/current/include ${RedBox_BINARY_DIR}/Dependencies/include/)
endif(iphone)




#we copy the header private and public header files
file(MAKE_DIRECTORY ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include/RedBox)
configure_file(${Public_RedBox_Headers} ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include COPYONLY)
foreach(privateHeader ${Private_RedBox_Headers})
	configure_file(${privateHeader} ${RedBox_BINARY_DIR}/${CMAKE_BUILD_TYPE}/include/RedBox COPYONLY)
endforeach(privateHeader ${Private_RedBox_Headers})


link_directories( ${RedBox_BINARY_DIR}/Dependencies/lib/)
		

	add_library(RedBox STATIC ${RedBoxSources} ${RedBoxHeaders})
	target_link_libraries(
	RedBox
	png
	freetype
	z
	${RedBox_libraries_list}
	)



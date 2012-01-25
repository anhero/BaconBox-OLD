get_filename_component(Helper_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Headers ${Helper_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Sources ${Helper_dir}/*.cpp)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	include(${Helper_dir}/libc/Sources.cmake)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	include(${Helper_dir}/libc/Sources.cmake)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(WIN32)
	include(${Helper_dir}/Windows/Sources.cmake)
endif(WIN32)

if(iphone)
	include(${Helper_dir}/ios/Sources.cmake)
endif(iphone)

include(${Helper_dir}/Tween/Sources.cmake)
include(${Helper_dir}/Serialization/Sources.cmake)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Sources})


source_group(RedBox\\Helper  FILES ${RedBox_RedBox_Helper_Sources} ${RedBox_RedBox_Helper_Headers})


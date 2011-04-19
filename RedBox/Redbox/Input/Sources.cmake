get_filename_component(Input_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
include(${Input_dir}/Accelerometer/Sources.cmake)
include(${Input_dir}/GamePad/Sources.cmake)
include(${Input_dir}/Keyboard/Sources.cmake)
include(${Input_dir}/Pointer/Sources.cmake)

if(${SDL})
	include(${Input_dir}/SDL/Sources.cmake)
endif(${SDL})

file(GLOB RedBox_RedBox_Input_Headers ${Input_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Sources ${Input_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Sources})


source_group(RedBox\\Input  FILES ${RedBox_RedBox_Input_Sources} ${RedBox_RedBox_Input_Headers})


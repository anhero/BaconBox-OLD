get_filename_component(Keyboard_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
if(${QT})
	include(${Keyboard_dir}/Qt/Sources.cmake)
endif(${QT})

if(${SDL})
	include(${Keyboard_dir}/SDL/Sources.cmake)
endif(${SDL})

file(GLOB RedBox_RedBox_Input_Keyboard_Headers ${Keyboard_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Keyboard_Sources ${Keyboard_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Keyboard_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Keyboard_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Keyboard_Sources})


source_group(RedBox\\Input\\Keyboard  FILES ${RedBox_RedBox_Input_Keyboard_Sources} ${RedBox_RedBox_Input_Keyboard_Headers})


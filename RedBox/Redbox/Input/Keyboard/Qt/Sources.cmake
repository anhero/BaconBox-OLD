get_filename_component(Qt_Keyboard_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_Keyboard_Qt_Headers ${Qt_Keyboard_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Keyboard_Qt_Sources ${Qt_Keyboard_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Keyboard_Qt_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Keyboard_Qt_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Keyboard_Qt_Sources})


source_group(RedBox\\Input\\Keyboard\\Qt  FILES ${RedBox_RedBox_Input_Keyboard_Qt_Sources} ${RedBox_RedBox_Input_Keyboard_Qt_Headers})


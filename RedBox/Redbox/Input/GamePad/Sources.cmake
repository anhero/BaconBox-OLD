get_filename_component(GamePad_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_GamePad_Headers ${GamePad_dir}/*.h)
file(GLOB RedBox_RedBox_Input_GamePad_Sources ${GamePad_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_GamePad_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_GamePad_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_GamePad_Sources})


source_group(RedBox\\Input\\GamePad  FILES ${RedBox_RedBox_Input_GamePad_Sources} ${RedBox_RedBox_Input_GamePad_Headers})


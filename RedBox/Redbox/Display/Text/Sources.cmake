get_filename_component(DisplayText_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Display_Text_Headers ${DisplayText_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Text_Sources ${DisplayText_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Text_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Text_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Text_Sources})


source_group(RedBox\\Display\\Text  FILES ${RedBox_RedBox_Display_Text_Sources} ${RedBox_RedBox_Display_Text_Headers})


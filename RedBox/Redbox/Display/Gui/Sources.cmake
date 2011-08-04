get_filename_component(DisplayGui_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Display_Gui_Headers ${DisplayGui_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Gui_Sources ${DisplayGui_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Gui_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Gui_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Gui_Sources})


source_group(RedBox\\Display\\Gui  FILES ${RedBox_RedBox_Display_Gui_Sources} ${RedBox_RedBox_Display_Gui_Headers})


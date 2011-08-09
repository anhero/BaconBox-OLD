get_filename_component(Display_Gui_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Display_Gui_Headers ${Display_Gui_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Gui_Sources ${Display_Gui_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Gui_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Gui_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Gui_Sources})


source_group(RedBox\\Display\\Gui  FILES ${RedBox_RedBox_Display_Gui_Sources} ${RedBox_RedBox_Display_Gui_Headers})


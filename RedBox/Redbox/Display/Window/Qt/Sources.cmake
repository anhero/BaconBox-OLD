get_filename_component(Display_Window_QT_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Display_Window_QT_Headers ${Display_Window_QT_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Window_QT_Sources ${Display_Window_QT_dir}/*.cpp)
file(GLOB RedBox_RedBox_Display_Window_QT_ui ${Display_Window_QT_dir}/*.ui)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Window_QT_Headers})

list(APPEND RedBox_QT_MOC_headers ${RedBox_RedBox_Display_Window_QT_Headers})
list(APPEND RedBox_QT_uis ${RedBox_RedBox_Display_Window_QT_ui})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Window_QT_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Window_QT_Sources})

source_group(RedBox\\Display\\Window\\QT  FILES ${RedBox_RedBox_Display_Window_QT_Sources} ${RedBox_RedBox_Display_Window_QT_Headers})


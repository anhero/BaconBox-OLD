get_filename_component(DisplayDriver_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Display_Driver_Headers ${DisplayDriver_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Driver_Sources ${DisplayDriver_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Driver_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Driver_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Driver_Sources})


source_group(RedBox\\Display\\Driver  FILES ${RedBox_RedBox_Display_Driver_Sources} ${RedBox_RedBox_Display_Driver_Headers})


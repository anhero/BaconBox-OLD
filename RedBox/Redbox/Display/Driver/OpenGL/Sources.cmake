get_filename_component(OpenGL_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Display_Driver_OpenGL_Headers ${OpenGL_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Driver_OpenGL_Sources ${OpenGL_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Driver_OpenGL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Driver_OpenGL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Driver_OpenGL_Sources})

source_group(RedBox\\Display\\Driver\\OpenGL  FILES ${RedBox_RedBox_Display_Driver_OpenGL_Sources} ${RedBox_RedBox_Display_Driver_OpenGL_Headers})


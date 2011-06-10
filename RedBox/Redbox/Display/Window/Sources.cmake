get_filename_component(Display_Window_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

if(SDL)
	include(${Display_Window_dir}/SDL/Sources.cmake)
endif(SDL)

file(GLOB RedBox_RedBox_Display_Window_Headers ${Display_Window_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Window_Sources ${Display_Window_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Window_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Window_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Window_Sources})


source_group(RedBox\\Display\\Window  FILES ${RedBox_RedBox_Display_Window_Sources} ${RedBox_RedBox_Display_Window_Headers})


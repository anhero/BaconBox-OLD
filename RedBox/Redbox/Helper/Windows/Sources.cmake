get_filename_component(Windows_Helper_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Windows_Headers ${Windows_Helper_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Windows_Sources ${Windows_Helper_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Windows_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Windows_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Windows_Sources})

source_group(RedBox\\Helper\\Windows  FILES ${RedBox_RedBox_Helper_Windows_Sources} ${RedBox_RedBox_Helper_Windows_Headers})


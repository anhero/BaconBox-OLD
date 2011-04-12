get_filename_component(Helper_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Headers ${Helper_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Sources ${Helper_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Sources})


source_group(RedBox\\Helper  FILES ${RedBox_RedBox_Helper_Sources} ${RedBox_RedBox_Helper_Headers})


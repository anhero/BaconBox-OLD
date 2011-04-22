get_filename_component(ios_Helper_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_ios_Headers ${ios_Helper_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_ios_Sources ${ios_Helper_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_ios_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_ios_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_ios_Sources})

source_group(RedBox\\Helper\\ios  FILES ${RedBox_RedBox_Helper_ios_Sources} ${RedBox_RedBox_Helper_ios_Headers})


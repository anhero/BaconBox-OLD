get_filename_component(OSX_Helper_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_OSX_Headers ${OSX_Helper_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_OSX_Sources ${OSX_Helper_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_OSX_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_OSX_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_OSX_Sources})

source_group(RedBox\\Helper\\OSX  FILES ${RedBox_RedBox_Helper_OSX_Sources} ${RedBox_RedBox_Helper_OSX_Headers})


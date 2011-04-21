get_filename_component(libc_Helper_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_libc_Headers ${libc_Helper_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_libc_Sources ${libc_Helper_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_libc_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_libc_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_libc_Sources})

source_group(RedBox\\Helper\\libc  FILES ${RedBox_RedBox_Helper_libc_Sources} ${RedBox_RedBox_Helper_libc_Headers})


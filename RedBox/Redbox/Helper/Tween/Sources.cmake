get_filename_component(Helper_Tween_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Tween_Headers ${Helper_Tween_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Tween_Sources ${Helper_Tween_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Tween_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Tween_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Tween_Sources})


source_group(RedBox\\Helper\\Tween  FILES ${RedBox_RedBox_Helper_Tween_Sources} ${RedBox_RedBox_Helper_Tween_Headers})


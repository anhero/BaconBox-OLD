get_filename_component(PointerIOS_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_Pointer_ios_Headers ${PointerIOS_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Pointer_ios_Sources ${PointerIOS_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Pointer_ios_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Pointer_ios_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Pointer_ios_Sources})


source_group(RedBox\\Input\\Pointer\\ios  FILES ${RedBox_RedBox_Input_Pointer_ios_Sources} ${RedBox_RedBox_Input_Pointer_ios_Headers})



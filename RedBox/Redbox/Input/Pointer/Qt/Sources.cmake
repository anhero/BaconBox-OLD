get_filename_component(PointerQt_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_Pointer_Qt_Headers ${PointerQt_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Pointer_Qt_Sources ${PointerQt_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Pointer_Qt_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Pointer_Qt_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Pointer_Qt_Sources})


list(APPEND RedBox_QT_MOC_headers ${RedBox_RedBox_Input_Pointer_Qt_Headers})


source_group(RedBox\\Input\\Pointer\\Qt  FILES ${RedBox_RedBox_Input_Pointer_Qt_Sources} ${RedBox_RedBox_Input_Pointer_Qt_Headers})


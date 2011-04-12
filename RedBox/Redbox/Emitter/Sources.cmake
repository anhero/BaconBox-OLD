get_filename_component(Emitter_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Emitter_Headers ${Emitter_dir}/*.h)
file(GLOB RedBox_RedBox_Emitter_Sources ${Emitter_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Emitter_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Emitter_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Emitter_Sources})


source_group(RedBox\\Emitter  FILES ${RedBox_RedBox_Emitter_Sources} ${RedBox_RedBox_Emitter_Headers})


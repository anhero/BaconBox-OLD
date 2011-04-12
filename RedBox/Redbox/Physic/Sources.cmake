get_filename_component(Physic_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Physic_Headers ${Physic_dir}/*.h)
file(GLOB RedBox_RedBox__Physic_Sources ${Physic_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Physic_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Physic_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox__Physic_Sources})


source_group(RedBox\\Physic  FILES ${RedBox_RedBox__Physic_Sources} ${RedBox_RedBox_Physic_Headers})


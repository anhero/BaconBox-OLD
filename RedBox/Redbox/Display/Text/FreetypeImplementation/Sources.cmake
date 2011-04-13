get_filename_component(FreetypeImplementation_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Display_Text_FreetypeImplementation_Headers ${FreetypeImplementation_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Text_FreetypeImplementation_Sources ${FreetypeImplementation_dir}/*.cpp)


list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Text_FreetypeImplementation_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Text_FreetypeImplementation_Sources})


source_group(RedBox\\Display\\Text\\FreetypeImplementation  FILES ${RedBox_RedBox_Display_Text_FreetypeImplementation_Sources} ${RedBox_RedBox_Display_Text_FreetypeImplementation_Headers})


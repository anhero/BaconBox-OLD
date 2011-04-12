get_filename_component(OpenAL_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Audio_OpenAL_Headers ${OpenAL_dir}/*.h)
file(GLOB RedBox_RedBox_Audio_OpenAL_Sources ${OpenAL_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Audio_OpenAL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Audio_OpenAL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Audio_OpenAL_Sources})


source_group(RedBox\\Audio\\OpenAL FILES ${RedBox_RedBox_Audio_OpenAL_Headers} ${RedBox_RedBox_Audio_OpenAL_Sources})


get_filename_component(MusicIOS_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Audio_MusicIOS_Headers ${MusicIOS_dir}/*.h)
file(GLOB RedBox_RedBox_Audio_MusicIOS_Sources ${MusicIOS_dir}/*.cpp *.m)


list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Audio_MusicIOS_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Audio_MusicIOS_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Audio_MusicIOS_Sources})

source_group(RedBox\\Audio\\MusicIOS  FILES ${RedBox_RedBox_Audio_MusicIOS_Sources} ${RedBox_RedBox_Audio_MusicIOS_Headers})

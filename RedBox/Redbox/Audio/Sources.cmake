get_filename_component(Audio_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

if(iphone)
	include(${Audio_dir}/MusicIOS/Sources.cmake)
elseif(SDL)
	include(${Audio_dir}/SDL/Sources.cmake)
elseif(QT)
	include(${Audio_dir}/OpenAL/Sources.cmake)
endif(iphone)

file(GLOB RedBox_RedBox_Audio_Headers ${Audio_dir}/*.h)
file(GLOB RedBox_RedBox_Audio_Sources ${Audio_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Audio_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Audio_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Audio_Sources})


source_group(RedBox\\Audio  FILES ${RedBox_RedBox_Audio_Sources} ${RedBox_RedBox_Audio_Headers})


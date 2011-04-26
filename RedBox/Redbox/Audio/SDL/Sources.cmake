get_filename_component(SDL_Mixer_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Audio_SDL_Headers ${SDL_Mixer_dir}/*.h)
file(GLOB RedBox_RedBox_Audio_SDL_Sources ${SDL_Mixer_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Audio_SDL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Audio_SDL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Audio_SDL_Sources})


source_group(RedBox\\Audio\\SDL FILES ${RedBox_RedBox_Audio_SDL_Headers} ${RedBox_RedBox_Audio_SDL_Sources})


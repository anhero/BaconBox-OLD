get_filename_component(SDL_Input_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Input_SDL_Headers ${SDL_Input_dir}/*.h)
file(GLOB RedBox_RedBox_Input_SDL_Sources ${SDL_Input_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_SDL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_SDL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_SDL_Sources})

source_group(RedBox\\Input\\SDL  FILES ${RedBox_RedBox_Input_SDL_Sources} ${RedBox_RedBox_Input_SDL_Headers})


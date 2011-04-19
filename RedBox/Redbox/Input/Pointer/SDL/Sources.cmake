get_filename_component(PointerSDL_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_Pointer_SDL_Headers ${PointerSDL_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Pointer_SDL_Sources ${PointerSDL_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Pointer_SDL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Pointer_SDL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Pointer_SDL_Sources})

source_group(RedBox\\Input\\Pointer\\SDL  FILES ${RedBox_RedBox_Input_Pointer_SDL_Sources} ${RedBox_RedBox_Input_Pointer_SDL_Headers})


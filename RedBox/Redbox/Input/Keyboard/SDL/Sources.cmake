get_filename_component(SDL_Keyboard_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_Keyboard_SDL_Headers ${SDL_Keyboard_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Keyboard_SDL_Sources ${SDL_Keyboard_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Keyboard_SDL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Keyboard_SDL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Keyboard_SDL_Sources})

source_group(RedBox\\Input\\Keyboard\\SDL  FILES ${RedBox_RedBox_Input_Keyboard_SDL_Sources} ${RedBox_RedBox_Input_Keyboard_SDL_Headers})


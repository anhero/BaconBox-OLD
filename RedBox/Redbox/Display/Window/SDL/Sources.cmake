get_filename_component(Display_Window_SDL_dir ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_Display_Window_SDL_Headers ${Display_Window_SDL_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Window_SDL_Sources ${Display_Window_SDL_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Window_SDL_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Window_SDL_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Window_SDL_Sources})

source_group(RedBox\\Display\\Window\\SDL  FILES ${RedBox_RedBox_Display_Window_SDL_Sources} ${RedBox_RedBox_Display_Window_SDL_Headers})


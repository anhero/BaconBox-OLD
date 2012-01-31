get_filename_component(Display_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
include(${Display_dir}/Driver/Sources.cmake)
include(${Display_dir}/Text/Sources.cmake)
include(${Display_dir}/Window/Sources.cmake)
include(${Display_dir}/Gui/Sources.cmake)
include(${Display_dir}/TileMap/Sources.cmake)

file(GLOB RedBox_RedBox_Display_Headers ${Display_dir}/*.h)
file(GLOB RedBox_RedBox_Display_Sources ${Display_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_Sources})


source_group(RedBox\\Display  FILES ${RedBox_RedBox_Display_Sources} ${RedBox_RedBox_Display_Headers})


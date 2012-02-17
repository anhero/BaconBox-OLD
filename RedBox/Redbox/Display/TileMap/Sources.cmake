get_filename_component(Display_TileMap_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Display_TileMap_Headers ${Display_TileMap_dir}/*.h)
file(GLOB RedBox_RedBox_Display_TileMap_Sources ${Display_TileMap_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_TileMap_Headers})

include(${Display_TileMap_dir}/TinyXML/Sources.cmake)

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_TileMap_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_TileMap_Sources})

source_group(RedBox\\Display\\TileMap  FILES ${RedBox_RedBox_Display_TileMap_Sources} ${RedBox_RedBox_Display_TileMap_Headers})


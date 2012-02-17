get_filename_component(Display_TileMap_TinyXML_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Display_TileMap_TinyXML_Headers ${Display_TileMap_TinyXML_dir}/*.h)
file(GLOB RedBox_RedBox_Display_TileMap_TinyXML_Sources ${Display_TileMap_TinyXML_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Display_TileMap_TinyXML_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Display_TileMap_TinyXML_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Display_TileMap_TinyXML_Sources})

source_group(RedBox\\Display\\TileMap\\TinyXML  FILES ${RedBox_RedBox_Display_TileMap_TinyXML_Sources} ${RedBox_RedBox_Display_TileMap_TinyXML_Headers})


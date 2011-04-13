get_filename_component(RedBox_root ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB Public_RedBox_Headers ${RedBox_root}/*.h)
source_group(RedBox FILES ${Public_RedBox_Headers})
list(APPEND RedBoxHeaders ${Public_RedBox_Headers})
include(${RedBox_root}/RedBox/Sources.cmake)
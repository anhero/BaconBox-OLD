get_filename_component(Helper_Serialization_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Serialization_Headers ${Helper_Serialization_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Serialization_Sources ${Helper_Serialization_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Serialization_Headers})

include(${Helper_Serialization_dir}/JsonBox/Sources.cmake)
include(${Helper_Serialization_dir}/TinyXML/Sources.cmake)

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Serialization_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Serialization_Sources})

source_group(RedBox\\Helper\\Serialization  FILES ${RedBox_RedBox_Helper_Serialization_Sources} ${RedBox_RedBox_Helper_Serialization_Headers})


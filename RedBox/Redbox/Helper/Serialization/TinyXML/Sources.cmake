get_filename_component(Helper_Serialization_TinyXML_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Serialization_TinyXML_Headers ${Helper_Serialization_TinyXML_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Serialization_TinyXML_Sources ${Helper_Serialization_TinyXML_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Serialization_TinyXML_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Serialization_TinyXML_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Serialization_TinyXML_Sources})


source_group(RedBox\\Helper\\Serialization\\TinyXML  FILES ${RedBox_RedBox_Helper_Serialization_TinyXML_Sources} ${RedBox_RedBox_Helper_Serialization_TinyXML_Headers})


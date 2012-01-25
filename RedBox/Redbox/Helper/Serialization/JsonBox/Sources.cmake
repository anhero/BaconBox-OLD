get_filename_component(Helper_Serialization_JsonBox_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Helper_Serialization_JsonBox_Headers ${Helper_Serialization_JsonBox_dir}/*.h)
file(GLOB RedBox_RedBox_Helper_Serialization_JsonBox_Sources ${Helper_Serialization_JsonBox_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Helper_Serialization_JsonBox_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Helper_Serialization_JsonBox_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Helper_Serialization_JsonBox_Sources})


source_group(RedBox\\Helper\\Serialization\\JsonBox  FILES ${RedBox_RedBox_Helper_Serialization_JsonBox_Sources} ${RedBox_RedBox_Helper_Serialization_JsonBox_Headers})


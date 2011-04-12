get_filename_component(Accelerometer_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
file(GLOB RedBox_RedBox_Input_Accelerometer_Headers  ${Accelerometer_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Accelerometer_Sources  ${Accelerometer_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Accelerometer_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Accelerometer_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Accelerometer_Sources})


source_group(RedBox\\Input\\Accelerometer  FILES ${RedBox_RedBox_Input_Accelerometer_Sources} ${RedBox_RedBox_Input_Accelerometer_Headers})


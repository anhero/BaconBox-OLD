get_filename_component(SignalSlots ${CMAKE_CURRENT_LIST_FILE} PATH)

file(GLOB RedBox_RedBox_SignalSlots_Headers ${SignalSlots}/*.h)
file(GLOB RedBox_RedBox_SignalSlots_Sources ${SignalSlots}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_SignalSlots_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_SignalSlots_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_SignalSlots_Sources})


source_group(RedBox\\SignalSlots  FILES ${RedBox_RedBox_SignalSlots_Sources} ${RedBox_RedBox_SignalSlots_Headers})


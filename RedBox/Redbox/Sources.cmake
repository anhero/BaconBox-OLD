get_filename_component(RedBox_subroot_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
include(${RedBox_subroot_dir}/Audio/Sources.cmake)
include(${RedBox_subroot_dir}/Display/Sources.cmake)
include(${RedBox_subroot_dir}/Emitter/Sources.cmake)
include(${RedBox_subroot_dir}/Helper/Sources.cmake)
include(${RedBox_subroot_dir}/Input/Sources.cmake)
include(${RedBox_subroot_dir}/SignalSlots/Sources.cmake)
include(${RedBox_subroot_dir}/SignalSlots/Sources.cmake)
#include(${RedBox_subroot_dir}/Physic/Sources.cmake)



file(GLOB RedBox_RedBox_Headers ${RedBox_subroot_dir}/*.h)
file(GLOB RedBox_RedBox_Sources ${RedBox_subroot_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Sources})

source_group(RedBox  FILES ${RedBox_RedBox_Sources} ${RedBox_RedBox_Headers})


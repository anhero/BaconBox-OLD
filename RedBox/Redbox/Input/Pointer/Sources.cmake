get_filename_component(Pointer_dir ${CMAKE_CURRENT_LIST_FILE} PATH)
if(${QT})
	include(${Pointer_dir}/Qt/Sources.cmake)
elseif(${SDL})
	include(${Pointer_dir}/SDL/Sources.cmake)
elseif(${iphone})
	include(${Pointer_dir}/ios/Sources.cmake)	
endif(${QT})

file(GLOB RedBox_RedBox_Input_Pointer_Headers ${Pointer_dir}/*.h)
file(GLOB RedBox_RedBox_Input_Pointer_Sources ${Pointer_dir}/*.cpp)

list(APPEND Private_RedBox_Headers ${RedBox_RedBox_Input_Pointer_Headers})

list(APPEND RedBoxHeaders ${RedBox_RedBox_Input_Pointer_Headers})
list(APPEND RedBoxSources ${RedBox_RedBox_Input_Pointer_Sources})


source_group(RedBox\\Input\\Pointer  FILES ${RedBox_RedBox_Input_Pointer_Sources} ${RedBox_RedBox_Input_Pointer_Headers})


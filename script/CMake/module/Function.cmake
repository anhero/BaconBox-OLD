
#Explore the given directory recursively and return a recursive list of all its subfolder 
#RecurseFolderList(<return variable> <path to the folder you want to explore>)
function(recurseFolderList folderList recurseFolderListPath) 
file(GLOB tempFileList  "${recurseFolderListPath}/*")
foreach(tempFile ${tempFileList} )
if(IS_DIRECTORY ${tempFile})
	recurseFolderList(tempFolderList "${tempFile}*" 1)
	list(APPEND tempFolderList ${tempFile})
endif(IS_DIRECTORY ${tempFile})
endforeach(tempFile)
set(${folderList} "${tempFolderList}" PARENT_SCOPE)
if(${ARGC} EQUAL 2)
list(APPEND tempFolderList ${recurseFolderListPath})
#foreach(tempAbsolute ${tempFolderList} )
#	file(RELATIVE_PATH tempRelative ${RedBox_BINARY_DIR}  ${tempAbsolute})
#		list(APPEND relativeList ${tempRelative})
#endforeach(tempAbsolute)
#set(${folderList} "${relativeList}" PARENT_SCOPE)
set(${folderList} "${tempFolderList}" PARENT_SCOPE)

endif(${ARGC} EQUAL 2)
endfunction(recurseFolderList)

#Copy a directory srcDir to a destination destDir
function(copy srcDir destDir)
  file(GLOB_RECURSE tempFiles RELATIVE ${srcDir} ${srcDir}/*)
  foreach(tempFile ${tempFiles})
    set(srcTempFilePath ${srcDir}/${tempFile})
    if(NOT IS_DIRECTORY ${srcTempFilePath})
      configure_file(${srcTempFilePath} ${destDir}/${tempFile} COPYONLY)
    endif(NOT IS_DIRECTORY ${srcTempFilePath})
  endforeach(tempFile)
endfunction(copy) 


macro(mm)
	if(${ARGC} EQUAL 0)
		message(STATUS "Parameter not set in mm function")
	endif(${ARGC} EQUAL 0)
	message(STATUS "${${ARGV0}}")
endmacro(mm)


MACRO(findpkg_framework fwk)
  IF(APPLE)
    SET(${fwk}_FRAMEWORK_PATH ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/
							  /Library/Frameworks/)
    FOREACH(dir ${${fwk}_FRAMEWORK_PATH})
      SET(fwkpath ${dir}/${fwk}.framework)
      IF(EXISTS ${fwkpath})
        SET(${fwk}_FRAMEWORK_INCLUDES ${${fwk}_FRAMEWORK_INCLUDES}
          ${fwkpath}/Headers )#${fwkpath}/PrivateHeaders)
        if (NOT ${fwk}_LIBRARY_FWK)
          SET(${fwk}_LIBRARY_FWK "-framework ${fwk}")
        endif ()
      ENDIF(EXISTS ${fwkpath})
    ENDFOREACH(dir)
  ENDIF(APPLE)
ENDMACRO(findpkg_framework)

macro(addFramework fwname appname)
    find_library(FRAMEWORK_${fwname}
        NAMES ${fwname}
        PATHS ${CMAKE_OSX_SYSROOT}/System/Library
        PATH_SUFFIXES Frameworks
        NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro(addFramework)


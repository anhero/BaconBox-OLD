include(function)


if(IPHONE)
	findpkg_framework("OpenGLES")
	set(OpenGL_LIBRARY_DIRS "" )
	set(OpenGL_INCLUDE_DIR OpenGLES_FRAMEWORK_INCLUDES )
	set(OpenGL_LIBRARIES OpenGLES_LIBRARY_FWK )

	#set(OpenGL_LIBRARY_DIRS "")
	#set(OpenGL_INCLUDE_DIR "")
	#set(OpenGL_LIBRARIES "")
	#addFramework(OpenGLES PROJECT_NAME)

elseif(redbox_QT)
#	set(OpenGL_LIBRARY_DIRS )
#	set(OpenGL_INCLUDE_DIR )
#	set(OpenGL_LIBRARIES )

endif(IPHONE)

MARK_AS_ADVANCED(
  OpenGL_LIBRARY_DIRS
  OpenGL_INCLUDE_DIR
  OpenGL_LIBRARIES
)

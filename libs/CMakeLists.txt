include_directories(
	glew-1.13.0/include/
)

set(GLEW_SOURCE
	glew-1.13.0/src/glew.c
	glew-1.13.0/src/glewinfo.c
	glew-1.13.0/src/visualinfo.c
)

set(GLEW_HEADERS
)


add_library( GLEW_1130 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1130
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)

set(LIBRARY_NAME ${DISPLAY3D_LIB})

include_directories(${CMAKE_SOURCE_DIR}/src/lib
					${OpenCV_INCLUDE_DIRS})
					
set(INCLUDE_FILES    Mesh.h
					 Shader.h
                     Texture.h
					 Camera.h)
set(SOURCE_FILES    Mesh.cpp
					Shader.cpp
					Texture.cpp
					Camera.cpp)
# make the library
add_library(
    ${LIBRARY_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
	)

SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${LIBRARY_NAME} ${OPENGL_LIBRARIES}
                                      ${OpenCV_LIBS}
									  ${GLUT_LIBRARY})

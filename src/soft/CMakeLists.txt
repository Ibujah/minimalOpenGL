set(source_files main.cpp)

#Déclaration de l'exécutable
set(EXEC_NAME exampleOpenGL)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/")
add_executable(${EXEC_NAME} ${source_files})

target_link_libraries(${EXEC_NAME} ${DISPLAY3D_LIB}
								   ${OPENGL_gl_LIBRARY}
								   ${OPENGL_glu_LIBRARY}
								   GLEW::GLEW
								   ${GLFW_LIBRARY})

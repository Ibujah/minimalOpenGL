cmake_minimum_required(VERSION 2.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(ExampleOpengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Enable C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(GLUT_ROOT_PATH $ENV{GLUT_ROOT_PATH})
list(APPEND CMAKE_PREFIX_PATH $ENV{GLEW_ROOT_PATH})

# Find the libraries
find_package(EIGEN REQUIRED)
find_package(OpenCV REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(GLFW REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/lib
					${CMAKE_SOURCE_DIR}/generated/
					${EIGEN_INCLUDE_DIRS}
					${OpenCV_INCLUDE_DIRS}
					${GLEW_INCLUDE_DIR}
					${GLM_INCLUDE_DIRS}
					${GLFW_INCLUDE_DIR})
					
if(NOT OPENGL_FOUND)
	message(ERROR " OPENGL not found!")
else()
	message(STATUS "-- Found OpenGL" )
endif(NOT OPENGL_FOUND)

link_directories(${OpenGL_LIBRARY_DIRS}
				 ${GLM_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS}
				${GLM_DEFINITIONS})

# define sub libraries name
set(DISPLAY3D_LIB "Display3D")

add_subdirectory(src/)


### CMake Entry Point ###

## < Project > ##
cmake_minimum_required (VERSION 3.1)
project(screw_engine)

## < Build Setting > ##

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (lib)

include_directories(
	lib/glfw/include/
	lib/glm/
	lib/glew/include/
	lib/assimp/include/
	lib/assimp/code/include
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_LIB
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
	-std=c++17
    -lGL
    -lGLU
    -lGLEW
    -lglfw
)

## < src > ##

add_executable(main
	src/main.cpp
	src/graphics/common.hpp
	src/graphics/system.hpp
	src/graphics/system.cpp
	src/graphics/input.hpp
	src/graphics/input.cpp
	src/graphics/graphics.hpp
	src/graphics/graphics.cpp
	src/graphics/shader.hpp
	src/graphics/shader.cpp
	src/graphics/callback.hpp
	src/graphics/callback.cpp
)

target_link_libraries(main
	${ALL_LIBS}
)
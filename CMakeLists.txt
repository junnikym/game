
### CMake Entry Point ###

## < Project > ##
cmake_minimum_required (VERSION 3.1)
project(screw_engine)

## < Build Setting > ##

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (lib)
find_package(ASSIMP REQUIRED)

include_directories(
	lib/glfw/include/
	lib/glm/
	lib/glew/include/
	lib/assimp/include/
	lib/assimp/code/include/
	lib/stb/
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_LIB
	assimp
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
	-lassimp
)

## < src > ##

add_executable(main
	src/main.cpp
	src/graphics/callback.hpp
	src/graphics/callback.cpp
	src/graphics/common.hpp
	src/graphics/graphics.hpp
	src/graphics/graphics.cpp
	src/graphics/input.hpp
	src/graphics/input.cpp
	src/graphics/integrate_types.hpp
	src/graphics/mesh.hpp
	src/graphics/mesh.cpp
	src/graphics/model.hpp
	src/graphics/model.cpp
	src/graphics/shader.hpp
	src/graphics/shader.cpp
	src/graphics/system.hpp
	src/graphics/system.cpp
	src/graphics/texture.hpp
	src/graphics/texture.cpp
)

target_link_libraries(main
	${ALL_LIBS}
)
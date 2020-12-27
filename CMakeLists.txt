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
	-g
)

## < config > ##

#configure_file(config/root.h.in config/root.h)
#include_directories(
#	${CMAKE_BINARY_DIR}/configuration
#)

## < src > ##

add_executable(main
	src/main.cpp

	# graphics

	src/graphics/callback.hpp
	src/graphics/callback.cpp
	src/graphics/camera.hpp
	src/graphics/camera.cpp
	src/graphics/graphics.hpp
	src/graphics/graphics.cpp
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

	# input 

	src/input/callback.hpp
	src/input/callback.cpp
	src/input/input.hpp
	src/input/input.cpp
	src/input/control.hpp
	src/input/control.cpp

	#math
	
	src/math/math_alias.hpp

	src/math/matrix.h
	src/math/matrix.hpp
	src/math/vector.h
	src/math/vector.hpp

	#physics
	
	src/physics/collision.hpp
	src/physics/collision.cpp
	src/physics/entity.hpp
	src/physics/entity.cpp
	src/physics/force.hpp
	src/physics/force.cpp
	src/physics/shape.hpp
	src/physics/shape.cpp

	# etc
	
	src/integrate_types.hpp
	src/common.hpp
)

target_link_libraries(main
	${ALL_LIBS}
)
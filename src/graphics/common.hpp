#ifndef COMMON_H

/**************************
 * Use which libaray
 **************************/
#define __OPENGL__

#include <iostream>
#include <algorithm>
#include <string>

#include <vector>

#include <fstream>
#include <sstream>

#include <cstdio>
#include <cstring>

using namespace std;

#ifdef _WIN32			// at windows OS

	#include <windwos.h>

#endif

#ifdef __OPENGL__		// alias common functions

	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
	#include <glm/glm.hpp>

	#include <assimp/Importer.hpp>
	#include <assimp/scene.h>
	#include <assimp/postprocess.h>

	using vector2 = glm::vec2;
	using vector3 = glm::vec3;
	using vector4 = glm::vec4;

#endif /* __OPENGL__ */

#include "integrate_types.hpp"

#endif /* COMMON_H */
#ifndef INTEGRATE_TYPES_HPP
#define INTEGRATE_TYPES_HPP

// Include
//--------------------------------------------------
#if defined(__OPENGL__)
	#include <glm/glm.hpp>
	#include <GLFW/glfw3.h>
#elif defined(__DX__)

#endif

#include "math/vector.hpp"

template<typename T>
using DictVector = std::vector<std::pair<std::string, T>>;

/*
 *	DEVICE :
 *		- OpenGL	: GLuint
 *		- DirectX	: ID3D11Device
 *
 * 	< Shader >
 * 
 *		VERTEX_SHADER :
 *			- OpenGL	: GLuint
 *			- DirectX	: ID3D11VertexShader
 * 
 * 		FRAGMENT_SHADER :
 * 			- OpenGL	: GLuint
 * 			- DirectX	: ID3D11PixelShader
 * 
 * 		SHADER : 
 * 			- OpenGL	: GLuint
 * 			- DirectX	: 
 * 
 *	BUFFER : 
 *		- OpenGL 	: ID3D11Device
 *		- DirectX 	: ID3D11Buffer
 *
 *	TEXTURE :
 * 		- OpenGL	: GLuint
 * 		- DirectX	: ID3D11Device
 * 
 * 	TIMER :
 * 		- OpenGL	: glfwGetTime();
 * 		- DirectX	: 
 */

#if defined(__OPENGL__)
	using DEVICE = GLuint;

	// < Shader >
	using VERTEX_SHADER = GLuint;
	using FRAGMENT_SHADER = GLuint;
	using SHADER = GLuint;

	using BUFFER = GLuint;
	using TEXTURE = GLuint;

	// < Vector >
	using vector2 = glm::vec2;
	using vector3 = glm::vec3;
	using vector4 = glm::vec4;

	// < matrix >
	using matrix4 = glm::mat4;

	constexpr auto get_time = glfwGetTime;

#elif defined(__DX__)
	using DEVICE = ID3D11Device;

	// < Shader >
	using VERTEX_SHADER = ID3D11VertexShader;
	using FRAGMENT_SHADER = ID3D11PixelShader;
	using SHADER = NULL; // ?

	using BUFFER = ID3D11Buffer;
	using TEXTURE = ID3D11Device;

	// < Vector >
	/* @ TODO : alias vectors
	using vector2 = 
	using vector3 = 
	using vector4 = 
	*/

	// < matrix >
	/* @ TODO : alias vectors
	using matrix4 = glm::mat4;
	*/
#endif

/* --------------------------------------------------
 * functions
 -------------------------------------------------- */

template <class T>
vector3 math_vec_to_glm_vec3(const math::Vector<T>& vec) {
	int copy_until = 3;
	vector3 result;
	
	if ( vec.size() < 3 )
		copy_until = vec.size();

	result.x = vec.get(0);	result.y = vec.get(1);	result.z = vec.get(2);

	return result;
} 

/* --------------------------------------------------
 * Structures
 -------------------------------------------------- */

struct VERTEX_TYPE {
	vector3 position;
	vector3 normal;
	vector2 texture;
	vector3 tangent;
	vector3 bitangent; 
};

// Enumerator

enum class MOVEMENT : unsigned int{
	forward  = 0,
	backward = 1,
	left 	 = 2,
	right	 = 3,
};

enum class DIRECTION {
	up,			// positive + Y
	down,		// negative - Y
	right,		// positive + X
	left,		// negative - X
	forward,	// positive + Z
	backward,	// negative - Z
};

enum class ROTATION_AXIS {
	yaw = 0,
	pitch = 1,
	roll = 2,
};

#endif
#ifndef INTEGRATE_TYPES_HPP
#define INTEGRATE_TYPES_HPP

// Include
//--------------------------------------------------
#if defined(__OPENGL__)
	#include <glm/glm.hpp>
#elif defined(__DX__)

#endif

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

enum class MOVEMENT {
	forward,
	backward,
	left,
	right,
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
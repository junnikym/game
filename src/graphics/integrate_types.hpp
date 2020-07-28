#ifndef INTEGRATE_TYPES_HPP
#define INTEGRATE_TYPES_HPP

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
#elif defined(__DX__)
	using DEVICE = ID3D11Device;

	// < Shader >
	using VERTEX_SHADER = ID3D11VertexShader;
	using FRAGMENT_SHADER = ID3D11PixelShader;
	using SHADER = NULL; // ?

	using BUFFER = ID3D11Buffer;
	using TEXTURE = ID3D11Device;
#endif

// Structures

struct VERTEX_TYPE {
	vector3 position;
	vector3 normal;
	vector2 texture;
	vector3 tangent;
	vector3 bitangent; 
};

#endif
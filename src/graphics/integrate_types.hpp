#ifndef INTEGRATE_TYPES_HPP
#define INTEGRATE_TYPES_HPP

/*
 *	DEVICE :
 *		- OpenGL	: GLuint
 *		- DirectX	: ID3D11Device
 *	
 *	BUFFER : 
 *		- OpenGL 	: ID3D11Device
 *		- DirectX 	: ID3D11Buffer
 */

#if defined(__OPENGL__)
	using DEVICE = GLuint;
	using BUFFER = GLuint;
#elif defined(__DX__)
	using DEVICE = ID3D11Device;
	using BUFFER = ID3D11Buffer;
#endif

#endif
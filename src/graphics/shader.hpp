#ifndef SHADER_H
#define SHADER_H

#include "common.hpp"

namespace graphics { 

class Shader {
	public:
		Shader();

		void initialize();
		void shutdown();
	private:

	#if defined(__OPENGL__)
		bool load_shader( const char* vertex_path, const char* fragment_path );
	#elif defined(__DX__)
		bool load_shader( const char* vertex_path, const char* fragment_path );
	#endif

	#if defined(__OPENGL__)
		GLuint m_shader;
		GLuint m_vertex;
		GLuint m_fragment;
	#elif defined(__DX__)
		ID3D11VertexShader* m_vertex
		ID3D11PixelShader* m_fragment;
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;
	#endif
};

} // end of namespace : graphics


#endif
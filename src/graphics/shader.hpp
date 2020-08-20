#ifndef SHADER_HPP
#define SHADER_HPP

#include "../common.hpp"

namespace graphics { 

/****************************************************************************
 *	Shaders			| Class
 * 
 *  
 ****************************************************************************/

class Shader {
	public:
		Shader() = default;
		Shader( const char* vertex_path, const char* fragment_path );

		void initialize();
		void shutdown();

		bool load( const char* vertex_path, const char* fragment_path );
		SHADER get();
		void use();

		void set_mat4(const string& key, const matrix4& value) const;
		
	private:
		bool load_shader( const char* vertex_path, const char* fragment_path );

		bool check_error(const GLuint& shader, const string& type);

		VERTEX_SHADER m_vertex;
		FRAGMENT_SHADER m_fragment;

		SHADER m_shader;

	#if defined(__OPENGL__)
		
	#elif defined(__DX__)
		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_matrixBuffer;
	#endif
};

static std::map<string, Shader> g_shaders;

} // end of namespace : graphics


#endif
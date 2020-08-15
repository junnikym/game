#include "shader.hpp"

namespace graphics { 

Shader::Shader( const char* vertex_path, const char* fragment_path ) {
	if ( ! this->load(vertex_path, fragment_path) ) {
		cout << "fail to load shader" << endl;
		this->initialize();
	}
}

void Shader::initialize() {
	#if defined(__OPENGL__)

		m_shader = 0;
		m_vertex = 0;
		m_fragment = 0;

	#elif defined(__DX__)

	#endif
}

void Shader::shutdown() {

#if defined(__OPENGL__)
	glDetachShader(m_shader, m_vertex);
	glDetachShader(m_shader, m_fragment);
	
	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);

#elif defined(__DX__)

#endif

}

bool Shader::load( const char* vertex_path, const char* fragment_path ) {
	this->shutdown();
	this->initialize();
	return this->load_shader(vertex_path, fragment_path);
}

SHADER Shader::get() {
	return this->m_shader;
}

void Shader::use() {

#if defined(__OPENGL__) 
	glUseProgram(m_shader); 
#endif

}

void Shader::set_mat4(const string& key, const matrix4& value) const {
	glUniformMatrix4fv( 
		glGetUniformLocation(m_shader, key.c_str()),
		1,
		GL_FALSE,
		&value[0][0]
	);
}

bool Shader::load_shader( const char* vertex_file_path, const char* fragment_file_path ) {

	string vs_code, fs_code;
	ifstream vs_file, fs_file;
	stringstream vs_stream, fs_stream;

	vs_file.exceptions ( ifstream::failbit | ifstream::badbit );
    fs_file.exceptions ( ifstream::failbit | ifstream::badbit );

	try {
		vs_file.open(vertex_file_path);
		fs_file.open(fragment_file_path);

		vs_stream << vs_file.rdbuf();
		fs_stream << fs_file.rdbuf();

		vs_file.close();
		fs_file.close();

		vs_code = vs_stream.str();
		fs_code = fs_stream.str();
	}
	catch ( ifstream::failure& e ) {
		cout << "Error : Fail to read shader file" << endl;
	}

	const char* vs_code_cstr = vs_code.c_str();
	const char* fs_code_cstr = fs_code.c_str();

	bool result = true;

	m_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertex, 1, &vs_code_cstr, NULL);
	glCompileShader(m_vertex);
	result = check_error(m_vertex, "vertex");

	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragment, 1, &fs_code_cstr, NULL);
	glCompileShader(m_fragment);
	result = check_error(m_fragment, "fragment");

	m_shader = glCreateProgram();
	glAttachShader(m_shader, m_vertex);
	glAttachShader(m_shader, m_fragment);
	glLinkProgram(m_shader);
	result = check_error(m_shader, "program");

	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);

	return result;
}

bool Shader::check_error(const GLuint& shader, const string& type) {
	GLint success = 0;
	GLchar log[1024] = "";

	if(type == "program") {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, log);
			cout << "( " << type << " ) shader link error : " << log << endl;

			return false;
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, log);
			cout << "( " << type << " ) shader compile error : " << log << endl;

			return false;
		}
	}

	return true;
}


} // end of namespace : graphics
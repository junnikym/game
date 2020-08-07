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

bool Shader::load_shader( const char* vertex_file_path, const char* fragment_file_path ) {
	// Create the shaders
	m_vertex = glCreateShader(GL_VERTEX_SHADER);
	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string vertex_code;
	ifstream vertex_stream(vertex_file_path, std::ios::in);
	if( vertex_stream.is_open() ) {
		std::stringstream sstr;
		sstr << vertex_stream.rdbuf();
		vertex_code = sstr.str();
		vertex_stream.close();
	} else {
		cout << "Fail to open shader : "<< vertex_file_path << endl;
		getchar();
		return false;
	}

	// Read the Fragment Shader code from the file
	string fragment_code;
	ifstream fragment_stream(fragment_file_path, std::ios::in);
	if( fragment_stream.is_open() ) {
		stringstream sstr;
		sstr << fragment_stream.rdbuf();
		fragment_code = sstr.str();
		fragment_stream.close();
	} else {
		cout << "Fail to open shader : "<< fragment_file_path << endl;
		getchar();
		return false;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	// Compile and Check Vertex Shader
	//-------------------------------------------------------

	// Compile Vertex Shader
	cout << "Compiling shader : " << vertex_file_path << endl;
	char const * VertexSourcePointer = vertex_code.c_str();
	glShaderSource(m_vertex, 1, &VertexSourcePointer , NULL);
	glCompileShader(m_vertex);

	// Check Vertex Shader
	glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_vertex, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(m_vertex, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("fragment shader error : \n%s\n", &VertexShaderErrorMessage[0]);

		this->shutdown();
		return false;
	}

	// Compile and Check Fragment Shader
	//-------------------------------------------------------

	// Compile Fragment Shader
	cout << "Compiling shader : " << fragment_file_path << endl;
	char const * FragmentSourcePointer = fragment_code.c_str();
	glShaderSource(m_fragment, 1, &FragmentSourcePointer , NULL);
	glCompileShader(m_fragment);

	// Check Fragment Shader
	glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_fragment, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(m_fragment, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("fragment shader error : \n%s\n", &FragmentShaderErrorMessage[0]);

		this->shutdown();
		return false;
	}

	// Link Shaders to Program
	//-------------------------------------------------------

	// Link the program
	m_shader = glCreateProgram();
	glAttachShader(m_shader, m_vertex);
	glAttachShader(m_shader, m_fragment);
	glLinkProgram(m_shader);

	// Check the program
	glGetProgramiv(m_shader, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(m_shader, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("Error when link shader to program : \n%s\n", &ProgramErrorMessage[0]);

		this->shutdown();
		return false;
	}

	return true;
}


} // end of namespace : graphics
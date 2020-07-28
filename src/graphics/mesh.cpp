#include "mesh.hpp"

namespace graphics {

/****************************************************************************
 *	Mesh			| Class
 * 
 *  Manage vertices
 ****************************************************************************/

Mesh::Mesh() {
	m_vertex_buf = nullptr;
	m_index_buf = nullptr;
}

Mesh::Mesh( 
		DEVICE* device, 
		const vector<VERTEX_TYPE>& vertices, 
		const vector<unsigned int>& indices,
		const vector<Texture>& textures 
) {
	this->intialize(device, vertices, indices, textures);
}

void Mesh::intialize( 
	DEVICE* device, 
	const vector<VERTEX_TYPE>& vertices, 
	const vector<unsigned int>& indices,
	const vector<Texture>& textures 
) {
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_textures = textures;

	setup_mesh_buf(device);
}

void Mesh::release() {
	release_mesh_buf();
}

void Mesh::draw(Shader &shader) {
	string name = "";
	string number = "";


	// bind appropriate textures
	unsigned int diffuse_i	= 1;
	unsigned int specular_i	= 1;
	unsigned int normal_i	= 1;
	unsigned int height_i	= 1;

	for(unsigned int i = 0; i < m_textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		name = m_textures[i].type();

		/*----- Reflectance properties  -----*/

		if(name == "texture_diffuse")
			number = std::to_string(diffuse_i++);

		else if(name == "texture_specular")
			number = std::to_string(normal_i++);

		else if(name == "texture_normal")
			number = std::to_string(normal_i++);

		else if(name == "texture_height")
			number = std::to_string(height_i++);

		glUniform1i(
			glGetUniformLocation(shader.get(), (name + number).c_str()), i);

		// and finally bind the texture
		glBindTexture( GL_TEXTURE_2D, m_textures[i].get() );
	}

	// Draw mesh
	glBindVertexArray( *m_VAO );
	glDrawElements( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setup_mesh_buf(DEVICE* device) {

	VERTEX_TYPE* vertices;
	unsigned long* indices;

#if defined(__OPENGL__)

	m_VAO = new GLuint;

	m_vertex_buf = new BUFFER;
	m_index_buf = new BUFFER;

#elif defined(__DX__)

	//D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	//D3D11_SUBRESOURCE_DATA vertexData, indexData;

#endif

#if defined(__OPENGL__)

	// Generate Buffers
	glGenVertexArrays ( 1, m_VAO );
	glGenBuffers ( 1, m_vertex_buf );
	glGenBuffers ( 1, m_index_buf );

	// Vertex Array Object
	glBindVertexArray ( *m_VAO );

	// Vertex Buffer Object
	glBindBuffer ( GL_ARRAY_BUFFER, *m_vertex_buf );
	glBufferData ( GL_ARRAY_BUFFER, 
				   m_vertices.size() * sizeof(VERTEX_TYPE), 
				   &m_vertices[0], 
				   GL_STATIC_DRAW );

	// Index Buffer Object
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, *m_index_buf );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, 
				   m_indices.size() * sizeof(unsigned int), 
				   &m_indices[0], 
				   GL_STATIC_DRAW );

	// -- Read Attribute --

	// Vertex Position
	glEnableVertexAttribArray ( 0 );
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( VERTEX_TYPE ), (void*)0 );
	// Vertex Normals
	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_TYPE), (void*)offsetof(VERTEX_TYPE, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_TYPE), (void*)offsetof(VERTEX_TYPE, texture));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_TYPE), (void*)offsetof(VERTEX_TYPE, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_TYPE), (void*)offsetof(VERTEX_TYPE, bitangent));

	glBindVertexArray(0);
	
#elif defined(__DX__)

#endif

}

void Mesh::release_mesh_buf() {

	#if defined(__OPENGL__)
		glDeleteVertexArrays( 1, m_VAO);
	#endif

	// Release the index buffer. 
	if( m_index_buf != nullptr ) { 
	
		#if defined(__OPENGL__)
			glDeleteBuffers( 1, m_index_buf);
			delete m_index_buf;
		#elif defined(__DX__)
			m_index_buf->Release(); 
		#endif
		
		m_index_buf = nullptr; 
	}

	// Release the vertex buffer. 
	if( m_vertex_buf != nullptr ) { 
		
		#if defined(__OPENGL__)
			glDeleteBuffers( 1, m_vertex_buf);
			delete m_vertex_buf;
		#elif defined(__DX__)
			m_vertex_buf->Release(); 
		#endif

		m_vertex_buf = nullptr;
	}

}


} // end of namespace : graphics
#include "model.hpp"

namespace graphics {

/****************************************************************************
 *	Model			| Class
 * 
 *  Process input through graphics lib
 ****************************************************************************/

Model::Model() {
	m_vertex_buf = nullptr;
	m_index_buf = nullptr;

	m_vertex_count = 0;
	m_index_count = 0;

	#if defined(__OPENGL__)

	#elif defined(__DX__)
		
	#endif
}

bool Model::initialize(DEVICE* device, string texture_path) {
	bool result = false;

	result = initialize_buf(device);
	if( ! result ) {
		cout << "fail to initialize model buffers" << endl;
		return false;
	}
}

void Model::shutdown() {

}

bool Model::initialize_buf(DEVICE* device) {

#if defined(__OPENGL__)
	VERTEX_TYPE* vertices;
	unsigned long* indices;
	
	//D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	//D3D11_SUBRESOURCE_DATA vertexData, indexData;

	#if defined(__OPENGL__)
		GLuint VAO;		// Vertex Array Object

		m_vertex_buf = new BUFFER;
		m_index_buf = new BUFFER;
	#elif defined(__DX__)

	#endif

	// Generate Buffers
	glGenVertexArrays ( 1, &VAO );
	glGenBuffers ( 1, m_vertex_buf );
	glGenBuffers ( 1, m_index_buf );

	// Vertex Array Object
	glBindVertexArray ( VAO );

	// Vertex Buffer Object
	glBindBuffer ( GL_ARRAY_BUFFER, *m_vertex_buf );
	glBufferData ( GL_ARRAY_BUFFER, m_vertex_count, vertices, GL_STATIC_DRAW );

	// Index Buffer Object
	glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, *m_index_buf );
	glBufferData ( GL_ELEMENT_ARRAY_BUFFER, m_index_count, indices, GL_STATIC_DRAW );

	// -- Read Attribute --

	// position
	glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)0 );
	glEnableVertexAttribArray ( 0 );
	// color 
	glVertexAttribPointer ( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)(3 * sizeof ( float )) );
	glEnableVertexAttribArray ( 1 );		// Indices
	// texture coord
	glVertexAttribPointer ( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof ( float ), (void*)(6 * sizeof ( float )) );
	glEnableVertexAttribArray ( 2 );		// Texture
	
#elif defined(__DX__)

#endif

}

void Model::release_buf() {
	glDeleteBuffers(buf_obj->n, &buf_obj->VAO);			// 등록된 객체를 해제 시켜줌
	glDeleteBuffers(buf_obj->n, &buf_obj->VBO);
	glDeleteVertexArrays(buf_obj->n, &buf_obj->EBO);

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
		
	}
}


bool Model::load_model( const char* file_path, 
						 vector<vector3> & vertices,
						 vector<vector3> & color, 
						 vector<vector2> & uvs,
						 vector<vector3> & normals ) {

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
	if( !scene) {
		fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	const aiMesh* mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	vertices.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D pos = mesh->mVertices[i];
		vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	uvs.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	normals.reserve(mesh->mNumVertices);
	for(unsigned int i=0; i<mesh->mNumVertices; i++){
		aiVector3D n = mesh->mNormals[i];
		normals.push_back(glm::vec3(n.x, n.y, n.z));
	}


	// Fill face indices
	indices.reserve(3*mesh->mNumFaces);
	for (unsigned int i=0; i<mesh->mNumFaces; i++){
		// Assume the model has only triangles.
		indices.push_back(mesh->mFaces[i].mIndices[0]);
		indices.push_back(mesh->mFaces[i].mIndices[1]);
		indices.push_back(mesh->mFaces[i].mIndices[2]);
	}
	
	// The "scene" pointer will be deleted automatically by "importer"

}


} // end of namespace : graphics
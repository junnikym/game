#ifndef MESH_H
#define MESH_H

#include "common.hpp"

#include "shader.hpp"
#include "texture.hpp"

namespace graphics {

/****************************************************************************
 *	Mesh			| Class
 * 
 *  Manage vertices
 ****************************************************************************/

class Mesh {
	public:
		Mesh();
		Mesh( 
			DEVICE* device, 
			const vector<VERTEX_TYPE>& vertices, 
			const vector<unsigned int>& indices,
			const vector<Texture>& textures 
		);

		void intialize( 
			DEVICE* device, 
			const vector<VERTEX_TYPE>& vertices, 
			const vector<unsigned int>& indices,
			const vector<Texture>& textures 
		);

		void release();

		void draw(Shader &shader);
	private:
		void setup_mesh_buf(DEVICE* device);
		void release_mesh_buf();

	private:
		// Mesh Data
		vector<VERTEX_TYPE> m_vertices;
		vector<unsigned int> m_indices;
		vector<Texture>	m_textures;

		// Buffers
		BUFFER *m_vertex_buf, *m_index_buf;

	#if defined(__OPENGL__) 
		GLuint *m_VAO;
	#endif
};


} // end of namespace : graphics

#endif
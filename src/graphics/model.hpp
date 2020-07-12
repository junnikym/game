#ifndef MODEL_H
#define MODEL_H

#include "common.hpp"

namespace graphics {

class Model {
	private:
		struct VERTEX_TYPE {
			vector3 position;
			vector4 color;
			vector2 texture;
		};

	public:
		Model();

		bool initialize(DEVICE* device, string texture_path);
		void shutdown();
		void render();

		int get_index_count();

	private:

		bool initialize_buf(DEVICE* device);
		void release_buf();

		bool load_model( const char* file_path, 
						 vector<vector3> & vertices,
						 vector<vector3> & color, 
						 vector<vector2> & uvs,
						 vector<vector3> & normals );
	
	// Buffers
		BUFFER *m_vertex_buf, *m_index_buf;

		int m_vertex_count, m_index_count;
};

} // end of namespace : graphics

#endif
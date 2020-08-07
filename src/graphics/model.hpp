#ifndef MODEL_H
#define MODEL_H

#include "mesh.hpp"

namespace graphics {

/****************************************************************************
 *	Model			| Class
 * 
 *  Process input through graphics lib
 ****************************************************************************/

class Model {
	public:
		Model();
		Model( const char* path, int gamma = 0 );

		void initialize( const char* path, int gamma );

		void draw(Shader& s);

	private:
		void load_model(string const &path);
		
		void process_node(aiNode *node, const aiScene *scene);
		Mesh process_mesh(aiMesh *mesh, const aiScene *scene);

		vector<Texture> load_material_textures( 
			aiMaterial *mat, 
			aiTextureType type, 
			string typeName 
		);

	/* ===== ===== ===== ===== =====
	 *	Members 
	===== ===== ===== ===== ===== */

		vector<Mesh> m_meshes;
		string directory;
		int gamma_correction;
		vector<Texture> textures_loaded;
};

} // end of namespace : graphics

#endif
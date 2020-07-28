#include "model.hpp"

namespace graphics {

/****************************************************************************
 *	Model			| Class
 * 
 *  Process input through graphics lib
 ****************************************************************************/

Model::Model() {
	directory = "";
	gamma_correction = 0;
}

Model::Model( const char* path, int gamma ) {
	initialize(path, gamma);
}

void Model::initialize( const char* path, int gamma ) {
	this->gamma_correction = gamma;

	load_model(path);
}

void Model::draw(Shader& s) {
	for(auto& elem : m_meshes) 
		elem.draw(s);
}

void Model::load_model(string const &path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile( 
		path,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace
	);

	if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "Can not load model via AssImp : " << importer.GetErrorString() << endl;
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode *node, const aiScene *scene) {

	for(unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back( process_mesh(mesh, scene) );
	}
	
	for(unsigned int i = 0; i < node->mNumChildren; i++) {
		process_node( node->mChildren[i], scene );
	}

}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
	vector<VERTEX_TYPE> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	VERTEX_TYPE vertex;
	vector3 vec;
	vector2 texture_vec;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
		
		// positions
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.position = vec;

		// normals
		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		vertex.normal = vec;

		// texture coordinates
		if(mesh->mTextureCoords[0]) {
			texture_vec.x = mesh->mTextureCoords[0][i].x; 
			texture_vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texture = texture_vec;
		}
		else {
			vertex.texture = vector2(0.0f, 0.0f);
		}

		// tangent
		vec.x = mesh->mTangents[i].x;
		vec.y = mesh->mTangents[i].y;
		vec.z = mesh->mTangents[i].z;
		vertex.tangent = vec;
		
		// bitangent
		vec.x = mesh->mBitangents[i].x;
		vec.y = mesh->mBitangents[i].y;
		vec.z = mesh->mBitangents[i].z;
		vertex.bitangent = vec;

		vertices.push_back(vertex);
	}
	

	for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}


	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 1. diffuse maps
	vector<Texture> diffuseMaps 	= load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	// 2. specular maps
	vector<Texture> specularMaps 	= load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// 3. normal maps
	std::vector<Texture> normalMaps	= load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// 4. height maps
	std::vector<Texture> heightMaps	= load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// ! - ! - ! - ! - ! - ! - ! - ! - ! - ! - ! - //
	// @TODO : will modify device parameter
	return Mesh( nullptr, vertices, indices, textures);
	// ! - ! - ! - ! - ! - ! - ! - ! - ! - ! - ! - //
}

vector<Texture> Model::load_material_textures(
	aiMaterial *material, 
	aiTextureType type,
	string type_name
) {
	
	vector<Texture> textures;
	int comp = 0;

	aiString str;
	bool skip = false;

	for(unsigned int i = 0; i < material->GetTextureCount(type); i++) {

		material->GetTexture(type, i, &str);
		skip = false;

		for(unsigned int j = 0; j < textures_loaded.size(); j++) {

			comp = std::strcmp(textures_loaded[j].path().data(), str.C_Str());

			if(comp == 0) {
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}

		}

		if(!skip) {
			Texture temp;
			
			temp.load(str.C_Str());
			temp.set_type(type_name.c_str());

			textures.push_back(temp);
			textures_loaded.push_back(temp);
		}

	}

	return textures;
}


} // end of namespace : graphics
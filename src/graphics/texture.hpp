#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define STB_IMAGE_IMPLEMENTATION

#include "../common.hpp"

namespace graphics {

/****************************************************************************
 *	Texture			| Class
 * 
 *  Load and process texture file for model
 ****************************************************************************/

class Texture {
	public:
		Texture();
		Texture(DEVICE* device, const string& path);

		bool initialize(const string& path);
		void shutdown();

		TEXTURE get();
		string type();
		string path();
		string filename();
		string directory();

		bool load(const string& directory, const string& filename, bool gamma = false);
		void set_type(const string& type);
	private:
		TEXTURE m_texture;
		string m_type;
		string m_filename;
		string m_directory;
};


} // end of namespace : graphics

#endif
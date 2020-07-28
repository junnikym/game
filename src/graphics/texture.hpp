#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define STB_IMAGE_IMPLEMENTATION

#include "common.hpp"

namespace graphics {

/****************************************************************************
 *	Texture			| Class
 * 
 *  Load and process texture file for model
 ****************************************************************************/

class Texture {
	public:
		Texture();
		Texture(DEVICE* device, const char* path);

		bool initialize(const char* path);
		void shutdown();

		TEXTURE get();
		string type();
		string path();

		bool load(const char* path, bool gamma = false);
		void set_type(const char* type);
	private:
		TEXTURE m_texture;
		string m_type;
		string m_path;
};


} // end of namespace : graphics

#endif
#include "texture.hpp"

namespace graphics {

/****************************************************************************
 *	Texture			| Class
 * 
 *  Load and process texture file for model
 ****************************************************************************/

Texture::Texture() { 
	
}

Texture::Texture(DEVICE* device, const string& path) {

}

TEXTURE Texture::get() {
	return this->m_texture;
}

string Texture::type() {
	return this->m_type;
}

string Texture::path() {
	return (m_directory + "/" + m_filename);
}

string Texture::filename() {
	return m_filename;
}

string Texture::directory() {
	return m_directory;
}

bool Texture::load(const string& directory, const string& filename, bool gamma) {
	this->m_directory = directory;
	this->m_filename = filename;

	string path = this->path();

	glGenTextures(1, &m_texture);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);

		return false;
	}

	return true;
}

void Texture::set_type(const string& type) {
	this->m_type = type;
}


} // end of namespace : graphics
#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

namespace Singularity
{

	Texture::Texture(const std::string& fileName)
	{
		int width, height, numComponents;
		unsigned char * imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
		
		if (imageData == NULL)
			std::cerr << "Texture at \"" << fileName << "\" failed to load." << std::endl;

		glGenTextures(1, &_textureID); // Allocates a buffer for the texture data.
		glBindTexture(GL_TEXTURE_2D, _textureID); // Uses the current texture.


		/// These are for repeating the texture. (If we try to get the 513th pixel on a 512x512 pixel texture, we will get pixel 1.
		/// We need 2 for height and width.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		/// These are used for magnification and minification of the textures.
		/// If we have a 512x512 texture but we need to use it in 256x256 or 1024x1024 scenarios.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		stbi_image_free(imageData);
	}

	void Texture::Bind(unsigned unit) 
	{
		assert(unit >= 0 && unit < 32); // OpenGL can only handle up to 32 slots. So we need to assert.

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, _textureID); // All future texture operation will use _textureId, until another bind is called.
	}


	Texture::~Texture()
	{
		glDeleteTextures(1, &_textureID);
	}
}

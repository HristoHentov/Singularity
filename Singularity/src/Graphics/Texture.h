#pragma once
#include <string>
#include <GLEW/glew.h>

namespace Singularity
{
	class Texture
	{
	public:
		Texture(const std::string& fileName);
		void Bind(unsigned int unit);

		
		virtual ~Texture();

	private:
		Texture(const Texture& other){}
		void operator = (const Texture& other){}

		GLuint _textureID;
	};

}

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <GLEW/glew.h>
#include "../Transform.h"
#include "../Camera.h"

namespace Singularity
{
	class Shader
	{
	public:
		Shader(const std::string& fileName);

		void Bind();
		void Update(const Transform& transform, const Camera& camera); // Updates all the uniforms.

		virtual ~Shader();

	private:
		static const unsigned int NUM_SHADERS = 2; // the number of shaders to use.

		enum
		{
			TRANSFORM_U,
			NUM_UNIFORMS
		};

		GLuint _program;
		GLuint _shaders[NUM_SHADERS];
		GLuint _uniforms[NUM_UNIFORMS];

		
	};

}

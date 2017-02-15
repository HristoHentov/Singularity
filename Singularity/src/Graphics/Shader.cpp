#include "Shader.h"

//#include "../../include/GLEW/glew.h"

namespace Singularity
{
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string path);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);

	Shader::Shader(const std::string& fileName)
	{

		_program = glCreateProgram();
		_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
		_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

		for (int i = 0; i < NUM_SHADERS; ++i) // Attach loaded shaders into current program.
			glAttachShader(_program, _shaders[i]);

		glBindAttribLocation(_program, 0, "position");
		glBindAttribLocation(_program, 1, "texCoord"); // used to bind mesh text coord to shader text coord.
		glBindAttribLocation(_program, 2, "normal");

		glLinkProgram(_program); // Link shaders
		CheckShaderError(_program, GL_LINK_STATUS, true, "ERROR! Shader linking failed.");

		glValidateProgram(_program); // Validate shader programs.
		CheckShaderError(_program, GL_VALIDATE_STATUS, true, "ERROR! Shader validation failed.");

		_uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");
	}


	Shader::~Shader()
	{

		for (int i = 0; i < NUM_SHADERS; ++i)
		{
			glDetachShader(_program, _shaders[i]);
			glDeleteShader(_shaders[i]);
		}

		glDeleteProgram(_program);
	}

	void Shader::Bind()
	{
		glUseProgram(_program);
	}

	void Shader::Update(const Transform& transform, const Camera& camera)
	{
		// if matrix math fails set GL_FALSE to GL_TRUE
		mat4 model = camera.GetViewProjection() * transform.GetModel();
		glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_TRUE, model.elements); //omfg if this works
	}

	static std::string LoadShader(const std::string path)
	{
		std::ifstream shaderFile;
		shaderFile.open(path);

		std::string output;
		std::string line;

		if (shaderFile.is_open())
		{
			while (shaderFile.good())
			{
				std::getline(shaderFile, line);
				output.append(line + "\n");
			}
		}
		else
		{
			std::cerr << "Unable to load shader: " << path << std::endl;
		}

		return output;

	}

	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram)
			glGetProgramiv(shader, flag, &success);
		else
			glGetShaderiv(shader, flag, &success);

		if(success == GL_FALSE)
		{
			if (isProgram)
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			else
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);

			std::cerr << errorMessage << ": " << error << "'" << std::endl;
		}
	}

	static GLuint CreateShader(const std::string& text, GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		if(shader == 0)
			std::cerr << "ERROR: Shader creation failed!" << std::endl;
		
		const GLchar* p[1];
		p[0] = text.c_str();
		GLint lengths[1];
		lengths[0] = text.length();

		glShaderSource(shader, 1, p, lengths);
		glCompileShader(shader);

		CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR! Shader compilation failed.");

		return shader;
	}

}

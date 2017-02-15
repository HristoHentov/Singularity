#pragma once
#include "../Maths/Math.h"
#include "../obj_loader.h"
#include "GLEW/glew.h"

namespace Singularity
{
	using namespace Maths;
	class Vertex
	{
	public:
		Vertex(const vec3& position, const vec2& texCoord, const vec3& normal = vec3(0,0,0))
		{
			this -> _position = position;
			this -> _textureCoordinate = texCoord;
			this-> _normal = normal;
		}

		inline vec3 * GetPosition() { return &_position; }
		inline vec2 * GetTexCoord() { return &_textureCoordinate; }
	private:
		vec3 _position;
		vec3 _normal;
		vec2 _textureCoordinate;
	};

	class Mesh
	{
	public:
		Mesh(const std::string& modelPath);
		Mesh(Vertex* vertices, unsigned int vertexCount, unsigned int * indicies, unsigned int indexCount); // indexes are used for draw order
		virtual ~Mesh();
		void Draw();

	private:

		Mesh(const Mesh& other);
		void operator = (const Mesh& other);
		void InitMesh(const IndexedModel& model);

		enum
		{
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,
			INDEX_VB,
			NUM_BUFFERS
		};

		GLuint _vertexArrayObject; // Standar OpenGL mesh data object. GL 3.3 and adobe.
		GLuint _vertexArrayBuffers[NUM_BUFFERS];

		unsigned int _drawCount; // how much of the Vertex Arrray object OpenGL should draw. 
	};

}

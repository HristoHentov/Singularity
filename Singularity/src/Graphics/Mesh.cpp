#include "Mesh.h"
#include <vector>
#include "../obj_loader.h"
#include <iostream>

namespace Singularity
{
	Mesh::Mesh(Vertex* vertices, unsigned int vertexCount, unsigned int * indicies, unsigned int indexCount)
	{
		// the whole point of this is to load all the mesh data so you can draw it and process it throught different shaders
//		IndexedModel model;
//		
//		for (unsigned int i = 0; i < vertexCount; i++)
//		{
//			model.positions.push_back(*vertices[i].GetPosition());
//			model.texCoords.push_back(*vertices[i].GetTexCoord());
//		}
//
//		for (unsigned int i = 0; i < indexCount; i++)
//		{
//			model.indices.push_back(*indicies[i]);
//		}
//
//		InitMesh(model);
	}

	Mesh::Mesh(const std::string& modelPath)
	{
		IndexedModel model = OBJModel(modelPath).ToIndexedModel();
		std::cout << "Model succesfully loaded." << std::endl;
		InitMesh(model);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &_vertexArrayObject);
	}

	void Mesh::Draw()
	{
		glBindVertexArray(_vertexArrayObject);

		glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);
//		glDrawArrays(GL_TRIANGLES, 0, _drawCount);

		glBindVertexArray(0);
	}

	void Mesh::InitMesh(const IndexedModel& model)
	{
		_drawCount = model.indices.size();

		glGenVertexArrays(1, &_vertexArrayObject);
		glBindVertexArray(_vertexArrayObject);

		glGenBuffers(NUM_BUFFERS, _vertexArrayBuffers);

		glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		/// -------------------------------------
		glBindBuffer(GL_ARRAY_BUFFER, _vertexArrayBuffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		///------------------------------------------

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexArrayBuffers[INDEX_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);

		std::cout << "Verticies: " << _drawCount << std::endl;
	}
}

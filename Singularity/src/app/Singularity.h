#pragma once
#include "../Graphics/Window.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Mesh.h"


namespace Singularity
{
	using namespace Singularity;
	class Singularity
	{

	public:
		Singularity(std::string windowName, int width, int height, vec3 cameraPosition, float fov);
		void Run();
		void Update();

	private:
		Window * _window;
		Shader * _shader;
		Texture * _texture;
		Camera * _camera;
		Mesh *_mesh;

		Transform _tMatrix;
		float _counter;
		vec3 _cameraPosition;
	};
	
}

#pragma once
#include "../Graphics/Window.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Mesh.h"
#include "Singularity.h"


#define TEXTURE_PATH "res/map.jpg"
#define SHADER_PATH  "res/shader"
#define MODEL_PATH   "res/plane.obj"


namespace Singularity
{
	 Singularity::Singularity(std::string windowName, int width, int height, vec3 cameraPosition, float fov)
		{
			this->_window = new Window(width, height, windowName);
			this->_camera = new Camera(cameraPosition, fov, ((float)width / (float)height), 0.01f, 1000.0f);
			this->_texture = new Texture(TEXTURE_PATH);
			this->_mesh = new Mesh(MODEL_PATH);
			this->_shader = new Shader(SHADER_PATH);
			_counter = 0;
		}

	void Singularity::Run()
		{
			while (!_window->IsClosed())
			{
				Update();
			}
		}

		void Singularity::Update()
		{
			_window->Clear(0.0f, 0.0f, 0.2f, 1.0f);
			//.GetRot().y = _counter * 10;
			_tMatrix.GetRot().x = _counter * 10;
			//_tMatrix.GetRot().z = _cameraPosition.z;

			_texture->Bind(0);
			_shader->Bind();
			_shader->Update(_tMatrix, *_camera);

			_mesh->Draw();
			_window->Update();

			_counter += 0.1f;
			_cameraPosition.z -= 0.25f;
		}
}
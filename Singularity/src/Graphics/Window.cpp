#include "Window.h"
#include <GLEW/glew.h>
#include "../Maths/vec4.h"
#include <iostream>

namespace Singularity
{
	Window::Window(int width, int height, const std::string& title)
	{
		_IsClosed = false;

		SDL_Init(SDL_INIT_EVERYTHING); // Not that smart to have all the SDL Initialization logic in the display class CTOR. 
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


		_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
		_GlContex = SDL_GL_CreateContext(_Window);

		GLenum status = glewInit();
		if (status != GLEW_OK)
		{
			std::cerr << "Failed to initialize GLEW!" << std::endl;
		}
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
	}


	void Window::Update()
	{
		SDL_GL_SwapWindow(_Window);
		SDL_Event Event;

		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT)
				_IsClosed = true;
		}
	}

	void Window::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::IsClosed()
	{
		return _IsClosed;
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(_GlContex);
		SDL_DestroyWindow(_Window);
		SDL_Quit();
	}
}

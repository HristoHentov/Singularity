#pragma once

#include <SDL2/SDL.H>
#include "../Maths/Math.h"
//#include "../../include/SDL2/SDL.h"

namespace Singularity
{
	using namespace Maths;

	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		void Update();
		void Clear(float r, float g, float b, float a);
		bool IsClosed();
		virtual ~Window();

	private:
		Window(const Window& other) {}
		void operator=(const Window& other) {}

		SDL_Window * _Window;
		SDL_GLContext _GlContex;
		bool _IsClosed;
	};

}

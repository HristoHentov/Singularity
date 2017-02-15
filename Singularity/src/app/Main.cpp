#include <iostream>
#include "../Graphics/Window.h"
#include "../app/Singularity.h"/
#include "../Maths/Math.h"
#include "../Maths/mat4.h"


#define WIDTH 720
#define HEIGHT 480

//using namespace Singularity;

int main(int argc, char ** argv)
{


	Singularity::Singularity sp("Singularity", 720, 480, Singularity::vec3(0, 0, -2.0f), 70.0f);
	sp.Run();

	return 0;
}


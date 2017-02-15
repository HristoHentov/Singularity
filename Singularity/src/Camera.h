#pragma once
#include "Math.h"
#include "Maths/mat4.h"

namespace Singularity
{
	using namespace Maths;
	class Camera
	{
	public:
		Camera(const vec3& pos, float fov, float aspect, float near, float far);

		void Update(const vec3& pos);

		inline mat4 GetViewProjection() const
		{
			return _perspective * mat4::LookAt(_position, _position + _forward, _up);
		}
	private:
		mat4 _perspective;
		vec3 _position;
		vec3 _forward; // defining the z axis
		vec3 _up; // defining the y axis
	};
}


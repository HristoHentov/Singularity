#include "Camera.h"


namespace Singularity {
	Camera::Camera(const vec3& pos, float fov, float aspect, float near, float far)
	{
		_perspective = mat4::Perspective(fov, aspect, near, far);
		_position = pos;
		_forward = vec3(0, 0, 1);
		_up = vec3(0, 1, 0);
	}

	void Camera::Update(const vec3& pos)
	{
		_position = pos;
	}
}

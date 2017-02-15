#include "Transform.h"


namespace Singularity {
	
	Transform::Transform(const vec3& pos, const vec3& rotation, const vec3& scale):
		_pos(pos),
		_rot(rotation),
		_scale(scale)
	{
	}
}

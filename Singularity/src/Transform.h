#pragma once
#include "Maths/Math.h"
namespace Singularity {

	using namespace Maths;
	class Transform
	{
	public:
		Transform(const vec3& pos = vec3(), const vec3& rotation = vec3(), const vec3& scale = vec3(1.0f, 1.0f, 1.0f));

		// Model matrix/world matrix - one that contains position,rotation,scale
		inline mat4 GetModel() const
		{
			mat4 posMatrix = mat4::Translate(_pos);
			mat4 scaleMatrix = mat4::Scale(_scale);
			mat4 rotXMatrix = mat4::Rotate(_rot.x, vec3(1, 0, 0));
			mat4 rotYMatrix = mat4::Rotate(_rot.y, vec3(0, 1, 0));
			mat4 rotZMatrix = mat4::Rotate(_rot.z, vec3(0, 0, 1));

			// Applies multiplication in reverse order (so X * Y * Z)
			mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix; 

			return posMatrix * rotMatrix * scaleMatrix;
		}

		inline vec3& GetPos() { return _pos; }
		inline vec3& GetRot() { return _rot; }
		inline vec3& GetScale() { return _scale; }

		inline void SetPos(vec3& pos) { _pos = pos; }
		inline void SetRot(vec3& rot) { _rot = rot; }
		inline void SetScale(vec3& scale) { _scale = scale; }


	private:
		vec3 _pos;
		vec3 _rot;
		vec3 _scale;


	};
}

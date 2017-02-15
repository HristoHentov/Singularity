#include "mat4.h"
#include <iostream>

namespace Singularity { namespace Maths {

	mat4::mat4()
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}

	mat4::mat4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}

	mat4& mat4::Multiply(const mat4& other)
	{
		float data[16];
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[e + row * 4] * other.elements[col + e * 4];
				}
				data[col + row * 4] = sum;
			}
		}
		memcpy(elements, data, 4 * 4 * sizeof(float));
		return *this;
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.Multiply(right);
	}

	mat4& mat4::operator*=(const mat4& other)
	{
		return Multiply(other);
	}

	mat4 mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[3 + 0 * 4] = (left + right) / (left - right);
		result.elements[3 + 1 * 4] = (bottom + top) / (bottom - top);
		result.elements[3 + 2 * 4] = (far + near) / (far - near);

		return result;
	}

	mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4 result(1.0f);

		float q = 1.0f / tan((0.5f * fov) * (M_PI / 180.0f));
		
		
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[2 + 3 * 4] = -1.0f;
		result.elements[3 + 2 * 4] = c;

		return result;
	}

	mat4 mat4::LookAt(const vec3& camera, const vec3& object, const vec3& up)
	{
		mat4 result = identity();
		vec3 f = (object - camera).Normalize();
		vec3 s = f.Cross(up.Normalize());
		vec3 u = s.Cross(f);

		result.elements[0 + 0 * 4] = s.x;
		result.elements[0 + 1 * 4] = s.y;
		result.elements[0 + 2 * 4] = s.z;

		result.elements[1 + 0 * 4] = u.x;
		result.elements[1 + 1 * 4] = u.y;
		result.elements[1 + 2 * 4] = u.z;

		result.elements[2 + 0 * 4] = -f.x;
		result.elements[2 + 1 * 4] = -f.y;
		result.elements[2 + 2 * 4] = -f.z;

		return result * Translate(vec3(-camera.x, -camera.y, -camera.z));
	}

	mat4 mat4::Translate(const vec3& translation)
	{
		mat4 result(1.0f);

		result.elements[3 + 0 * 4] = translation.x;
		result.elements[3 + 1 * 4] = translation.y;
		result.elements[3 + 2 * 4] = translation.z;

		return result;
	}

	mat4 mat4::Rotate(float angle, const vec3& axis)
	{
		mat4 result(1.0f);

		float r = angle * (M_PI / 180.0f);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[0 + 1 * 4] = y * x * omc + z * s;
		result.elements[0 + 2 * 4] = x * z * omc - y * s;

		result.elements[1 + 0 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[1 + 2 * 4] = y * z * omc + x * s;

		result.elements[2 + 0 * 4] = x * z * omc + y * s;
		result.elements[2 + 1 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	mat4 mat4::Scale(const vec3& scale)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		
		return result;
	}

	
	vec4 operator*(const mat4& left, const vec4& right)
	{
		return left.Multiply(right);
	}

	vec4 mat4::Multiply(const vec4& other) const
	{
		std::cout << "TEST" << std::endl;
		return vec4();
//		return other.multiply(*this);
	}

	}
}

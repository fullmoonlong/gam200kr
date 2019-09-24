/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: vec3.cpp
*	
*	Custom math library
*	2019/09/20
*/

#include <limits>	// absolute, epsilon
#include <cassert>	// assert
#include "vec3.h"

namespace Math
{
	void operator+=(vec3& v, const vec3& adding_vector) noexcept
	{
		v.x += adding_vector.x;
		v.y += adding_vector.y;
		v.z += adding_vector.z;
	}

	void operator-=(vec3& v, const vec3& subtracting_vector) noexcept
	{
		v.x -= subtracting_vector.x;
		v.y -= subtracting_vector.y;
		v.z -= subtracting_vector.z;
	}

	void operator*=(vec3& v, float scale) noexcept
	{
		v.x *= scale;
		v.y *= scale;
		v.z *= scale;
	}

	void operator/=(vec3& v, float divisor) noexcept
	{
		assert(divisor != 0.f);
		v.x /= divisor;
		v.y /= divisor;
		v.z /= divisor;
	}

	vec3 operator-(const vec3& v) noexcept
	{
		return vec3{ -v.x, -v.y, -v.z };
	}

	vec3 operator+(const vec3& v1, const vec3& v2) noexcept
	{
		return vec3{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}

	vec3 operator-(const vec3& v1, const vec3& v2) noexcept
	{
		return vec3{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}

	vec3 operator*(const vec3& v, float scale) noexcept
	{
		return vec3{ v.x * scale, v.y * scale, v.z * scale };
	}

	vec3 operator*(float scale, const vec3& v) noexcept
	{
		return v * scale;
	}

	vec3 operator/(const vec3& v, float divisor) noexcept
	{
		assert(divisor != 0.f);
		return vec3{ v.x / divisor, v.y / divisor, v.z / divisor };
	}

	bool operator==(const vec3& v1, const vec3& v2) noexcept
	{
		if (abs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() && abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon() && abs(v1.z - v2.z) <= std::numeric_limits<float>::epsilon())
		{
			return true;
		}
		return false;
	}

	bool operator!=(const vec3& v1, const vec3& v2) noexcept
	{
		if (v1 == v2)
		{
			return true;
		}
		return false;
	}

	float dot_product(vec3& v1, vec3& v2) noexcept
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	vec3 cross_product(vec3& v1, vec3& v2) noexcept
	{
		return vec3{ v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
	}

	float magnitude_squared(vec3 v) noexcept
	{
		return dot_product(v, v);
	}

	float magnitude(vec3 v) noexcept
	{
		return sqrt(magnitude_squared(v));
	}

	float distance_between(vec3 v1, vec3 v2) noexcept
	{
		return sqrt(magnitude_squared(v1 - v2));
	}

	float angle_between(vec3& v1, vec3& v2) noexcept
	{
		assert(magnitude(v1) != 0.f && magnitude(v2) != 0.f);
		return acos(dot_product(v1, v2) / (magnitude(v1) * magnitude(v2)));
	}
}

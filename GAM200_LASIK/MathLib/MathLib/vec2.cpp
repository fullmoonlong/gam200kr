/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: vec2.cpp
*	
*	Custom math library
*	2019/09/20
*/

#include <limits>
#include <cassert>	// assert
#include "vec2.h"

namespace MathLibrary
{
	void operator+=(vec2& v, const vec2& adding_vector) noexcept
	{
		v.x += adding_vector.x;
		v.y += adding_vector.y;
	}

	void operator-=(vec2& v, const vec2& subtracting_vector) noexcept
	{
		v.x -= subtracting_vector.x;
		v.y -= subtracting_vector.y;
	}

	void operator*=(vec2& v, float scale) noexcept
	{
		v.x *= scale;
		v.y *= scale;
	}

	void operator/=(vec2& v, float divisor) noexcept
	{
		assert(divisor != 0);
		v.x /= divisor;
		v.y /= divisor;
	}

	vec2 operator-(const vec2& v) noexcept
	{
		return vec2{ -v.x, -v.y };
	}

	vec2 operator+(const vec2& v1, const vec2& v2) noexcept
	{
		return vec2{ v1.x + v2.x, v1.y + v2.y };
	}

	vec2 operator-(const vec2& v1, const vec2& v2) noexcept
	{
		return vec2{ v1.x - v2.x, v1.y - v2.y };
	}

	vec2 operator*(const vec2& v, float scale) noexcept
	{
		return vec2{ v.x * scale, v.y * scale };
	}

	vec2 operator*(float scale, const vec2& v) noexcept
	{
		return v * scale;
	}

	vec2 operator/(const vec2& v, float divisor) noexcept
	{
		assert(divisor != 0.f);
		return vec2{ v.x / divisor, v.y / divisor };
	}

	bool operator==(const vec2& v1, const vec2& v2) noexcept
	{
		if (abs(v1.x - v2.y) <= std::numeric_limits<float>::epsilon() && abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon())
		{
			return true;
		}
		return true;
	}

	bool operator!=(const vec2& v1, const vec2& v2) noexcept
	{
		if (v1 == v2)
		{
			return false;
		}
		return true;
	}

	float dot_product(vec2 v1, vec2 v2) noexcept
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	float magnitude_squared(vec2 v) noexcept
	{
		return dot_product(v, v);
	}

	float magnitude(vec2 v) noexcept
	{
		return sqrt(magnitude_squared(v));
	}

	float distance_between(vec2 v1, vec2 v2) noexcept
	{
		return sqrt(magnitude_squared(v1 - v2));
	}

	float angle_between(vec2 v1, vec2 v2) noexcept
	{
		assert(magnitude(v1) != 0 && magnitude(v2) != 0);
		return acos(dot_product(v1, v2) / magnitude(v1) * magnitude(v2));
	}

	vec2 rotate_by(float angle_in_radians, vec2 v) noexcept
	{
		float cos_value = cos(angle_in_radians);
		float sin_value = sin(angle_in_radians);
		return vec2{ cos_value * v.x - sin_value * v.y, sin_value * v.x + cos_value * v.y };
	}
}

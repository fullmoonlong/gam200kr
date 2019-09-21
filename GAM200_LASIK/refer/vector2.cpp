/*
	Author: Jeonghak Kim
	Course: CS230
	Assignment: Math Programming Assignment
	Term: Spring 2019
*/


#include <CS230/math/vector2.hpp>
#include <cassert>
#include <limits>
#include <cmath>

namespace CS230
{
	vector2::vector2() noexcept
	{
		x = 0;
		y = 0;
	}

	vector2::vector2(float repeated_float) noexcept
	{
		x = repeated_float;
		y = repeated_float;
	}

	vector2::vector2(float fx, float fy) noexcept
	{
		x = fx;
		y = fy;
	}

	void operator+=(vector2 & v, const vector2 & adding_vector) noexcept
	{
		v.x += adding_vector.x;
		v.y += adding_vector.y;
	}

	void operator-=(vector2 & v, const vector2 & subtracting_vector) noexcept
	{
		v.x -= subtracting_vector.x;
		v.y -= subtracting_vector.y;
	}

	void operator*=(vector2 & v, float scale) noexcept
	{
		v.x *= scale;
		v.y *= scale;
	}

	void operator/=(vector2 & v, float divisor) noexcept
	{
		assert(divisor != 0.0f);
		v.x /= divisor;
		v.y /= divisor;
	}

	vector2 operator-(const vector2 & v) noexcept
	{
		return vector2(-v.x, -v.y);
	}

	vector2 operator+(const vector2 & v1, const vector2 & v2) noexcept
	{
		return vector2(v1.x + v2.x, v1.y + v2.y);
	}

	vector2 operator-(const vector2 & v1, const vector2 & v2) noexcept
	{
		return vector2(v1.x - v2.x, v1.y - v2.y);
	}

	vector2 operator*(const vector2 & v, float scale) noexcept
	{
		return vector2(scale * v.x, scale * v.y);
	}

	vector2 operator*(float scale, const vector2 & v) noexcept
	{
		return v * scale;
	}

	vector2 operator/(const vector2 & v, float divisor) noexcept
	{
		assert(divisor != 0.0f);
		return vector2(v.x / divisor, v.y / divisor);
	}

	bool operator==(const vector2 & v1, const vector2 & v2) noexcept
	{
		if (abs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() && abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(const vector2 & v1, const vector2 & v2) noexcept
	{
		if (v1 == v2)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	float dot(vector2 a, vector2 b) noexcept
	{
		return a.x * b.x + a.y * b.y;
	}

	vector2 perpendicular_to(vector2 a) noexcept
	{
		return vector2(-a.y, a.x);
	}

	float magnitude_squared(vector2 a) noexcept
	{
		return dot(a, a);
	}

	float magnitude(vector2 a) noexcept
	{
		return sqrt(magnitude_squared(a));
	}

	vector2 normalize(vector2 a) noexcept
	{
		return vector2(a / magnitude(a));
	}

	float distance_between_squared(vector2 a, vector2 b) noexcept
	{ 
		return magnitude_squared(a - b); /*(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);*/
	}

	float distance_between(vector2 a, vector2 b) noexcept 
	{
		return sqrt(distance_between_squared(a, b));
	}

	float angle_between(vector2 a, vector2 b) noexcept 
	{
		assert(magnitude(a) != 0 && magnitude(b) != 0);
		return acos(dot(a, b) / magnitude(a) * magnitude(b));
	}

	vector2 rotate_by(float angle_in_radians, vector2 v) noexcept
	{
		float cValue = cos(angle_in_radians);
		float sValue = sin(angle_in_radians);
		return vector2(cValue * v.x - sValue * v.y,
			           sValue * v.x + cValue * v.y);
	}

}

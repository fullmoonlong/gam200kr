/*
	Author: Jeonghak Kim
	Course: CS230
	Assignment: Math Programming Assignment
	Due_Date: 2019.03.13
*/


#include <CS230/math/vector3.hpp>
#include <cassert>
#include <limits>
#include <cmath>

namespace CS230
{
	vector3::vector3() noexcept
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vector3::vector3(float repeated_float) noexcept
	{
		x = repeated_float;
		y = repeated_float;
		z = repeated_float;
	}

	vector3::vector3(float fx, float fy, float fz) noexcept
	{
		x = fx;
		y = fy;
		z = fz;
	}

	void operator+=(vector3& v, const vector3& adding_vector) noexcept
	{
		v.x += adding_vector.x;
		v.y += adding_vector.y;
		v.z += adding_vector.z;
	}

	void operator-=(vector3& v, const vector3& subtracting_vector) noexcept
	{
		v.x -= subtracting_vector.x;
		v.y -= subtracting_vector.y;
		v.z -= subtracting_vector.z;
	}

	void operator*=(vector3& v, float scale) noexcept
	{
		v.x *= scale;
		v.y *= scale;
		v.z *= scale;
	}

	void operator/=(vector3& v, float divisor) noexcept
	{
		assert(divisor != 0.0f);
		v.x /= divisor;
		v.y /= divisor;
		v.z /= divisor;
	}

	vector3 operator-(const vector3& v) noexcept
	{
		return vector3(-v.x, -v.y, -v.z);
	}

	vector3 operator+(const vector3& v1, const vector3& v2) noexcept
	{
		return vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	vector3 operator-(const vector3& v1, const vector3& v2) noexcept
	{
		return vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	vector3 operator*(const vector3 & v, float scale) noexcept
	{
		return vector3(v.x * scale, v.y * scale, v.z * scale);
	}

	vector3 operator*(float scale, const vector3 & v) noexcept
	{
		return v * scale;
	}

	vector3 operator/(const vector3 & v, float divisor) noexcept
	{
		assert(divisor != 0.0f);
		return vector3(v.x / divisor, v.y / divisor, v.z / divisor);
	}

	bool operator==(const vector3 & v1, const vector3 & v2) noexcept
	{
		if (abs(v1.x - v2.x) <= std::numeric_limits<float>::epsilon() && abs(v1.y - v2.y) <= std::numeric_limits<float>::epsilon() && abs(v1.z - v2.z) <= std::numeric_limits<float>::epsilon())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(const vector3 & v1, const vector3 & v2) noexcept
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

	float dot(vector3 a, vector3 b) noexcept
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	vector3 cross(vector3 a, vector3 b) noexcept
	{
		return vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	float magnitude_squared(vector3 a) noexcept
	{
		return dot(a, a);
	}

	float magnitude(vector3 a) noexcept
	{
		return sqrt(magnitude_squared(a));
	}

	vector3 normalize(vector3 a) noexcept
	{
		return vector3(a / magnitude(a));
	}

	float distance_between_squared(vector3 a, vector3 b) noexcept
	{
		return magnitude_squared(a - b);
	}

	float distance_between(vector3 a, vector3 b) noexcept
	{
		return sqrt(distance_between_squared(a, b));
	}

	float angle_between(vector3 a, vector3 b) noexcept
	{
		assert(magnitude(a) != 0 && magnitude(b) != 0);
		return acos(dot(a, b) / (magnitude(a) * magnitude(b)));
	}

}
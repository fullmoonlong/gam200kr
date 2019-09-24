/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: vec3.h
*	
*	Custom math library
*	2019/09/20
*/

#pragma once

namespace Math
{
	class vec3
	{
	public:
		vec3() noexcept
			: x(0), y(0), z(0) {}

		vec3(float x, float y, float z) noexcept
			: x(x), y(y), z(z) {}

		vec3(float repeated_value) noexcept
			: x(repeated_value), y(repeated_value), z(repeated_value) {}
		float x, y, z;
	};

	void operator+=(vec3& v, const vec3& adding_vector) noexcept;

	void operator-=(vec3& v, const vec3& subtracting_vector) noexcept;

	void operator*=(vec3& v, float scale) noexcept;

	void operator/=(vec3& v, float divisor) noexcept;

	vec3 operator-(const vec3& v) noexcept;	// change sign

	vec3 operator+(const vec3& v1, const vec3& v2) noexcept;

	vec3 operator-(const vec3& v1, const vec3& v2) noexcept;

	vec3 operator*(const vec3& v, float scale) noexcept;

	vec3 operator*(float scale, const vec3& v) noexcept;

	vec3 operator/(const vec3& v, float divisor) noexcept;

	bool operator==(const vec3& v1, const vec3& v2) noexcept;

	bool operator!=(const vec3& v1, const vec3& v2) noexcept;

	float dot_product(vec3& v1, vec3& v2) noexcept;

	vec3 cross_product(vec3& v1, vec3& v2) noexcept;

	float magnitude_squared(vec3 v) noexcept;

	float magnitude(vec3 v) noexcept;

	float distance_between(vec3 v1, vec3 v2) noexcept;

	float angle_between(vec3& v1, vec3& v2) noexcept;
}

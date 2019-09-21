/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: vec2.h
*	
*	Custom math library
*	2019/09/20
*/

#pragma once

namespace MathLibrary
{
	class vec2
	{
	public:
		vec2() noexcept
			: x(0), y(0) {}

		vec2(float x, float y)
			: x(x), y(y) {}

		vec2(float repeated_value)
			: x(repeated_value), y(repeated_value) {}

		float x, y;
	};

	void operator+=(vec2& v, const vec2& adding_vector) noexcept;

	void operator-=(vec2& v, const vec2& subtracting_vector) noexcept;

	void operator*=(vec2& v, float scale) noexcept;

	void operator/=(vec2& v, float divisor) noexcept;

	vec2 operator-(const vec2& v) noexcept;

	vec2 operator+(const vec2& v1, const vec2& v2) noexcept;

	vec2 operator-(const vec2& v1, const vec2& v2) noexcept;

	vec2 operator*(const vec2& v, float scale) noexcept;

	vec2 operator*(float scale, const vec2& v) noexcept;

	vec2 operator/(const vec2& v, float divisor) noexcept;

	bool operator==(const vec2& v1, const vec2& v2) noexcept;

	bool operator!=(const vec2& v1, const vec2& v2) noexcept;

	float dot_product(vec2 v1, vec2 v2) noexcept;

	float magnitude_squared(vec2 v) noexcept;

	float magnitude(vec2 v) noexcept;

	float distance_between(vec2 v1, vec2 v2) noexcept;

	float angle_between(vec2 v1, vec2 v2) noexcept;

	vec2 rotate_by(float angle_in_radians, vec2 v) noexcept;
}
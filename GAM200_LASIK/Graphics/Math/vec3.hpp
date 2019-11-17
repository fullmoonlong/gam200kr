/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*
*	File_name: vec3.h
*
*	Custom math library
*	2019/09/20
*/

#pragma once

template <typename T>
class vec3
{
public:
	constexpr vec3() noexcept
		: x(0), y(0), z(0) {}

	constexpr vec3(T x, T y, T z) noexcept
		: x(x), y(y), z(z) {}

	constexpr vec3(T repeated_value) noexcept
		: x(repeated_value), y(repeated_value), z(repeated_value) {}
	T x, y, z;
};

template <typename T>
constexpr void operator+=(vec3<T>& v, const vec3<T>& adding_vector) noexcept
{
	v.x += adding_vector.x;
	v.y += adding_vector.y;
	v.z += adding_vector.z;
}

template <typename T>
constexpr void operator-=(vec3<T>& v, const vec3<T>& subtracting_vector) noexcept
{
	v.x -= subtracting_vector.x;
	v.y -= subtracting_vector.y;
	v.z -= subtracting_vector.z;
}

template <typename T>
constexpr void operator*=(vec3<T>& v, T scale) noexcept
{
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
}

template <typename T>
constexpr void operator/=(vec3<T>& v, T divisor) noexcept
{
	assert(divisor != 0.f);
	v.x /= divisor;
	v.y /= divisor;
	v.z /= divisor;
}

template <typename T>
constexpr vec3<T> operator-(const vec3<T>& v) noexcept
{
	return vec3<T>{ -v.x, -v.y, -v.z };
}

template <typename T>
constexpr vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) noexcept
{
	return vec3<T>{ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

template <typename T>
constexpr vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) noexcept
{
	return vec3<T>{ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

template <typename T>
constexpr vec3<T> operator*(const vec3<T>& v, T scale) noexcept
{
	return vec3<T>{ v.x* scale, v.y* scale, v.z* scale };
}

template <typename T>
constexpr vec3<T> operator*(T scale, const vec3<T>& v) noexcept
{
	return v * scale;
}

template <typename T>
constexpr vec3<T> operator/(const vec3<T>& v, T divisor) noexcept
{
	assert(divisor != 0.f);
	return vec3<T>{ v.x / divisor, v.y / divisor, v.z / divisor };
}

template <typename T>
constexpr bool operator==(const vec3<T>& v1, const vec3<T>& v2) noexcept
{
	if (abs(v1.x - v2.x) <= std::numeric_limits<T>::epsilon() && abs(v1.y - v2.y) <= std::numeric_limits<T>::epsilon() && abs(v1.z - v2.z) <= std::numeric_limits<T>::epsilon())
	{
		return true;
	}
	return false;
}

template <typename T>
constexpr bool operator!=(const vec3<T>& v1, const vec3<T>& v2) noexcept
{
	if (v1 == v2)
	{
		return true;
	}
	return false;
}

template <typename T>
constexpr T dot_product(vec3<T>& v1, vec3<T>& v2) noexcept
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
constexpr vec3<T> cross_product(vec3<T>& v1, vec3<T>& v2) noexcept
{
	return vec3<T>{ v1.y* v2.z - v1.z * v2.y, v1.z* v2.x - v1.x * v2.z, v1.x* v2.y - v1.y * v2.x };
}

template <typename T>
constexpr T magnitude_squared(vec3<T> v) noexcept
{
	return dot_product(v, v);
}

template <typename T>
constexpr T magnitude(vec3<T> v) noexcept
{
	return sqrt(magnitude_squared(v));
}

template <typename T>
constexpr T distance_between(vec3<T> v1, vec3<T> v2) noexcept
{
	return sqrt(magnitude_squared(v1 - v2));
}

template <typename T>
constexpr T angle_between(vec3<T>& v1, vec3<T>& v2) noexcept
{
	assert(magnitude(v1) != 0.f && magnitude(v2) != 0.f);
	return acos(dot_product(v1, v2) / (magnitude(v1) * magnitude(v2)));
}

template <typename T>
constexpr vec3<T> normalize(vec3<T>& v) noexcept
{
	T magnitude = magnitude(v);
	assert(magnitude != (T)0);
	return v / magnitude;
}

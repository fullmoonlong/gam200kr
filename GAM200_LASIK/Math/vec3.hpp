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
	constexpr void operator+=(vec3<T>& v, const vec3<T>& adding_vector) noexcept;
	template <typename T>
	constexpr void operator-=(vec3<T>& v, const vec3<T>& subtracting_vector) noexcept;
	template <typename T>
	constexpr void operator*=(vec3<T>& v, T scale) noexcept;
	template <typename T>
	constexpr void operator/=(vec3<T>& v, T divisor) noexcept;
	template <typename T>
	constexpr vec3<T> operator-(const vec3<T>& v) noexcept;	// change sign
	template <typename T>
	constexpr vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) noexcept;
	template <typename T>
	constexpr vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) noexcept;
	template <typename T>
	constexpr vec3<T> operator*(const vec3<T>& v, T scale) noexcept;
	template <typename T>
	constexpr vec3<T> operator*(T scale, const vec3<T>& v) noexcept;
	template <typename T>
	constexpr vec3<T> operator/(const vec3<T>& v, T divisor) noexcept;
	template <typename T>
	constexpr bool operator==(const vec3<T>& v1, const vec3<T>& v2) noexcept;
	template <typename T>
	constexpr bool operator!=(const vec3<T>& v1, const vec3<T>& v2) noexcept;
	template <typename T>
	constexpr T dot_product(vec3<T>& v1, vec3<T>& v2) noexcept;
	template <typename T>
	constexpr vec3<T> cross_product(vec3<T>& v1, vec3<T>& v2) noexcept;
	template <typename T>
	constexpr T magnitude_squared(vec3<T> v) noexcept;
	template <typename T>
	constexpr T magnitude(vec3<T> v) noexcept;
	template <typename T>
	constexpr T distance_between(vec3<T> v1, vec3<T> v2) noexcept;
	template <typename T>
	constexpr T angle_between(vec3<T>& v1, vec3<T>& v2) noexcept;
}

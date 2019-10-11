/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: vec2.h
*	
*	Custom math library
*	2019/09/20
*/

#pragma once

namespace Math
{
	template <typename T>
	class vec2
	{
	public:
		constexpr vec2() noexcept
			: x(0), y(0) {}

		constexpr vec2(T x, T y) noexcept
			: x(x), y(y) {}

		constexpr vec2(T repeated_value) noexcept
			: x(repeated_value), y(repeated_value) {}

		T x, y;
	};

	template <typename T>
	constexpr void operator+=(vec2<T>& v, const vec2<T>& adding_vector) noexcept;
	
	template <typename T>
	constexpr void operator-=(vec2<T>& v, const vec2<T>& subtracting_vector) noexcept;
	
	template <typename T>
	constexpr void operator*=(vec2<T>& v, T scale) noexcept;
	
	template <typename T>
	constexpr void operator/=(vec2<T>& v, T divisor) noexcept;
	
	template <typename T>
	constexpr vec2<T> operator-(const vec2<T>& v) noexcept;
	
	template <typename T>
	constexpr vec2<T> operator+(const vec2<T>& v1, const vec2<T>& v2) noexcept;
	
	template <typename T>
	constexpr vec2<T> operator-(const vec2<T>& v1, const vec2<T>& v2) noexcept;
	
	template <typename T>
	constexpr vec2<T> operator*(const vec2<T>& v, T scale) noexcept;
	
	template <typename T>
	constexpr vec2<T> operator*(T scale, const vec2<T>& v) noexcept;
	
	template <typename T>
	constexpr vec2<T> operator/(const vec2<T>& v, T divisor) noexcept;
	
	template <typename T>
	constexpr bool operator==(const vec2<T>& v1, const vec2<T>& v2) noexcept;
	
	template <typename T>
	constexpr bool operator!=(const vec2<T>& v1, const vec2<T>& v2) noexcept;
	
	template <typename T>
	constexpr T dot_product(vec2<T> v1, vec2<T> v2) noexcept;
	
	template <typename T>
	constexpr T magnitude_squared(vec2<T> v) noexcept;
	
	template <typename T>
	constexpr T magnitude(vec2<T> v) noexcept;
	
	template <typename T>
	constexpr T distance_between(vec2<T> v1, vec2<T> v2) noexcept;
	
	template <typename T>
	constexpr T angle_between(vec2<T> v1, vec2<T> v2) noexcept;
	
	template <typename T>
	constexpr vec2<T> rotate_by(float angle_in_radians, vec2<T> v) noexcept;

	template <typename T>
	constexpr vec2<T> rotate_by(float angle_in_radians, vec2<T> v) noexcept;

	template <typename T>
	constexpr vec2<T> normalize(vec2<T>& v) noexcept;
}

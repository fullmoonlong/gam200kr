/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: mat3.cpp
*	
*	Custom math library
*	2019/09/20
*/

#include <complex>	// cos, sin
#include <cassert>	// assert
#include "mat3.hpp"

namespace Math
{
	template <typename T>
	constexpr T mat3<T>::operator()(int column, int row) const noexcept
	{
		assert(0 <= column && column <= 2);
		assert(0 <= row && row <= 2);
		return elements[column][row];
	}

	template <typename T>
	constexpr T& mat3<T>::operator()(int column, int row) noexcept
	{
		assert(0 <= column && column <= 2);
		assert(0 <= row && row <= 2);
		return elements[column][row];
	}

	template <typename T>
	constexpr mat3<T> build_translation(T translate_x, T translate_y) noexcept
	{
		return mat3<T>{ 1, 0, 0,
			0, 1, 0,
			translate_x, translate_y, 1 };
	}

	template <typename T>
	constexpr mat3<T> build_rotation(float angle_in_radians) noexcept
	{
		return mat3<T>{ cos(angle_in_radians), sin(angle_in_radians), 0,
			-sin(angle_in_radians), cos(angle_in_radians), 0,
			0, 0, 1 };
	}

	template <typename T>
	constexpr mat3<T> build_scaling(T scale) noexcept
	{
		return mat3<T>{ scale, 0, 0,
			0, scale, 0,
			0, 0, 1 };
	}
	
}

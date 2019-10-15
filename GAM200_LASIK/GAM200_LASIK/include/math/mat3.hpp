/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*
*	File_name: mat3.h
*
*	Custom math library
*	2019/09/20
*/


#pragma once
#include <complex>	// cos, sin
#include <cassert>	// assert
#include <math/vec3.hpp>


template <typename T>
class mat3
{
public:
	constexpr mat3() noexcept
	{
		column[0].x = 0;
		column[0].y = 0;
		column[0].z = 0;

		column[1].x = 0;
		column[1].y = 0;
		column[1].z = 0;

		column[2].x = 0;
		column[2].y = 0;
		column[2].z = 0;
	}
	constexpr mat3(vec3<T> column0, vec3<T> column1, vec3<T> column2) noexcept
	{
		column[0] = column0;
		column[1] = column1;
		column[2] = column2;
	}
	constexpr mat3(T column0_row0, T column0_row1, T column0_row2,
		T column1_row0, T column1_row1, T column1_row2,
		T column2_row0, T column2_row1, T column2_row2)	noexcept
	{
		column[0].x = column0_row0;
		column[0].y = column0_row1;
		column[0].z = column0_row2;

		column[1].x = column1_row0;
		column[1].y = column1_row1;
		column[1].z = column1_row2;

		column[2].x = column2_row0;
		column[2].y = column2_row1;
		column[2].z = column2_row2;
	}

	union
	{
		T elements[3][3];
		vec3<T> column[3];
	};
	constexpr T operator() (int column, int row) const noexcept
	{
		assert(0 <= column && column <= 2);
		assert(0 <= row && row <= 2);
		return elements[column][row];
	}

	constexpr T& operator() (int column, int row) noexcept
	{
		assert(0 <= column && column <= 2);
		assert(0 <= row && row <= 2);
		return elements[column][row];
	}
};

//template <typename T>
//mat3<T> operator*(const mat3<T>& m1, const mat3<T>& m2) noexcept;

//template <typename T>
//void operator*=(mat3<T>& m1, const mat3<T>& m2) noexcept;

template <typename T>
constexpr mat3<T> build_translation(T translate_x, T translate_y) noexcept
{
	return mat3<T>{
		1, 0, 0,
		0, 1, 0,
		translate_x, translate_y, 1 };
}

template <typename T>
constexpr mat3<T> build_rotation(float angle_in_radians) noexcept
{
	return mat3<T>{
		cos(angle_in_radians), sin(angle_in_radians), 0,
		-sin(angle_in_radians), cos(angle_in_radians), 0,
		0, 0, 1 };
}

template <typename T>
constexpr mat3<T> build_scaling(T scale) noexcept
{
	return mat3<T>{
		scale, 0, 0,
		0, scale, 0,
		0, 0, 1 };
}

template <typename T>
constexpr mat3<T> build_scaling(T scale_x, T scale_y) noexcept
{
	return mat3<T>{
		scale_x, 0, 0,
		0, scale_y, 0,
		0, 0, 1};
}

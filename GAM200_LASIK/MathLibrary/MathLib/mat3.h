/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: mat3.h
*	
*	Custom math library
*	2019/09/20
*/

#pragma once
#include "vec3.h"

namespace Math
{
	template <typename T>
	class mat3
	{
	public:
		mat3() noexcept
		{
			column0.x = 0;
			column0.y = 0;
			column0.z = 0;

			column1.x = 0;
			column1.y = 0;
			column1.z = 0;

			column2.x = 0;
			column2.y = 0;
			column2.z = 0;
		}
		mat3(vec3<T> column0, vec3<T> column1, vec3<T> column2)	noexcept
			: column0(column0), column1(column1), column2(column2) {}
		mat3(T column0_row0, T column0_row1, T column0_row2,
			T column1_row0, T column1_row1, T column1_row2,
			T column2_row0, T column2_row1, T column2_row2)	noexcept
		{
			column0.x = column0_row0;
			column0.y = column0_row1;
			column0.z = column0_row2;

			column1.x = column1_row0;
			column1.y = column1_row1;
			column1.z = column1_row2;

			column2.x = column2_row0;
			column2.y = column2_row1;
			column2.z = column2_row2;
		}

		union
		{
			T elements[3][3];
			vec3<T> column0, column1, column2;
		};
		T operator() (int column, int row) const noexcept;
		T& operator() (int column, int row) noexcept;
	};

	//template <typename T>
	//mat3<T> operator*(const mat3<T>& m1, const mat3<T>& m2) noexcept;
	//template <typename T>
	//void operator*=(mat3<T>& m1, const mat3<T>& m2) noexcept;
	template <typename T>
	mat3<T> build_translation(T translate_x, T translate_y) noexcept;
	template <typename T>
	mat3<T> build_rotation(float angle_in_radians) noexcept;
	template <typename T>
	mat3<T> build_scaling(T scale) noexcept;
}

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
		mat3(vec3 column0, vec3 column1, vec3 column2)	noexcept
			: column0(column0), column1(column1), column2(column2) {}
		mat3(float column0_row0, float column0_row1, float column0_row2,
			float column1_row0, float column1_row1, float column1_row2,
			float column2_row0, float column2_row1, float column2_row2)	noexcept
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

		vec3 column0, column1, column2;
		//float operator() (int column, int row) const noexcept;
		//float& operator() (int column, int row) noexcept;
	};

	//mat3 operator*(const mat3& m1, const mat3& m2) noexcept;

	//void operator*=(mat3& m1, const mat3& m2) noexcept;
	mat3 build_translation(float translate_x, float translate_y) noexcept;
	mat3 build_rotation(float angle_in_radians) noexcept;
	mat3 build_scaling(float scale) noexcept;
}

/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: mat3.cpp
*	
*	Custom math library
*	2019/09/20
*/

#include "mat3.h"
#include <complex>	// cos, sin

namespace Math
{
	mat3 build_translation(float translate_x, float translate_y) noexcept
	{
		return mat3{ 1, 0, 0,
					0, 1, 0,
					translate_x, translate_y, 1 };
	}

	mat3 build_rotation(float angle_in_radians) noexcept
	{
		return mat3{ cos(angle_in_radians), sin(angle_in_radians), 0,
					-sin(angle_in_radians), cos(angle_in_radians), 0,
					0, 0, 1 };
	}

	mat3 build_scaling(float scale) noexcept
	{
		return mat3{ scale, 0, 0,
					0, scale, 0,
					0, 0 ,1 };
	}
}

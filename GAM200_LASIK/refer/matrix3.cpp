/*
	Author: Jeonghak Kim
	Course: CS230
	Assignment: Math Programming Assignment
	Due_Date: 2019.03.13
*/


#include <CS230/math/matrix3.hpp>
#include <CS230/math/vector2.hpp>
#include <cassert>
#include <limits>
#include <cmath>

namespace CS230
{
	matrix3::matrix3() noexcept
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

	matrix3::matrix3(vector3 first_column, vector3 second_column, vector3 third_column) noexcept
	{
		column0 = first_column;
		column1 = second_column;
		column2 = third_column;
	}

	matrix3::matrix3(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1, float column1_row2, float column2_row0, float column2_row1, float column2_row2) noexcept
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

	float matrix3::operator()(int column, int row) const noexcept
	{
		assert(0 <= column && column <= 2);
		assert(0 <= row && row <= 2);
		return elements[column][row];
	}

	float& matrix3::operator()(int column, int row) noexcept
	{
		assert(0 <= column && column <= 2);
		assert(0 <= row && row <= 2);
		return elements[column][row];
	}

	matrix3 operator*(const matrix3 & m1, const matrix3 & m2) noexcept
	{
		matrix3	m3;
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				m3.elements[i][j] =   m1.elements[0][j] * m2.elements[i][0] 
							    	+ m1.elements[1][j] * m2.elements[i][1] 
									+ m1.elements[2][j] * m2.elements[i][2];
			}
		}
		return m3;
	}

	void operator*=(matrix3 & m1, const matrix3 & m2) noexcept
	{
		m1 = m1 * m2;
	}

	vector3 operator*(const matrix3 & m, vector3 v) noexcept
	{
		vector3 v_result;
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				v_result.elements[i] += m.elements[j][i] * v.elements[j];
			}
		}
		return v_result;
	}

	matrix3 MATRIX3::transpose(const matrix3 & m) noexcept
	{
		return matrix3(m.column0.x, m.column1.x, m.column2.x,
					   m.column0.y, m.column1.y, m.column2.y,
					   m.column0.z, m.column1.z, m.column2.z);
	}

	matrix3 MATRIX3::build_rotation(float angle_in_radians) noexcept
	{
		matrix3 rotation;
		float cValue = cos(angle_in_radians);
		float sValue = sin(angle_in_radians);
		rotation.elements[0][0] = cValue;
		rotation.elements[0][1] = sValue;
		rotation.elements[0][2] = 0;

		rotation.elements[1][0] = -sValue;
		rotation.elements[1][1] = cValue;
		rotation.elements[1][2] = 0;

		rotation.elements[2][0] = 0;
		rotation.elements[2][1] = 0;
		rotation.elements[2][2] = 1;

		if (abs(cos(angle_in_radians)) <= std::numeric_limits<float>::epsilon())
		{
			rotation.elements[0][0] = 0;
			rotation.elements[1][1] = 0;
		}
		if (abs(sin(angle_in_radians)) <= std::numeric_limits<float>::epsilon())
		{
			rotation.elements[1][0] = 0;
			rotation.elements[0][1] = 0;
		}

		return rotation;
	}

	matrix3 MATRIX3::build_identity() noexcept
	{
		return matrix3(1, 0, 0,
					   0, 1, 0,
					   0, 0, 1);
	}

	matrix3 MATRIX3::build_scale(float scale_x, float scale_y) noexcept
	{
		return matrix3(scale_x, 0, 0,
					   0, scale_y, 0,
					   0, 0, 1);
	}

	matrix3 MATRIX3::build_scale(float scale) noexcept
	{
		return build_scale(scale, scale);
	}

    matrix3 MATRIX3::build_scale(const vector2 & scale) noexcept
    {
        return build_scale(scale.x, scale.y);
    }

	matrix3 MATRIX3::build_translation(float translate_x, float translate_y) noexcept
	{
		return matrix3(1, 0, 0,
					   0, 1, 0,
					   translate_x, translate_y, 1);
	}

	matrix3 MATRIX3::build_translation(const vector2 & translation) noexcept
	{
		return build_translation(translation.x, translation.y);
	}	
}

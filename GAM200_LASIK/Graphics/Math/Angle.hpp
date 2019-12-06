#pragma once

namespace ANGLE
{
	constexpr float pi = 3.1415926535897932384626433832795f;
	constexpr float two_pi = 2.0f * pi;
	constexpr float DegreeToRadian(float angle_in_degree) { return angle_in_degree * (pi / 180.0f); }
}
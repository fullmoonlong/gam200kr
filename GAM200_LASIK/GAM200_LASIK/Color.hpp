#pragma once
#include <algorithm>

class Color
{
public:
	Color(float same_intensity, float alpha = 1.0f)
	{
		const float new_color = std::clamp(same_intensity, 0.0f, 1.0f);
		r = new_color;
		g = new_color;
		b = new_color;
		a = alpha;
	}
	Color(float red, float green, float blue, float alpha = 1.0f)
	{
		r = std::clamp(red, 0.0f, 1.0f);
		g = std::clamp(green, 0.0f, 1.0f);
		b = std::clamp(blue, 0.0f, 1.0f);
		a = std::clamp(alpha, 0.0f, 1.0f);
	}
	
private:
	float r, g, b, a;
};
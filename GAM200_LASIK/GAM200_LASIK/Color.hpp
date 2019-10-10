#pragma once
#include <algorithm>

class Color
{
public:
	Color()
		: r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
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
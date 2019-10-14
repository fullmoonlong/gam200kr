#pragma once

class [[nodiscard]]Color4uc
{
public:
	Color4uc()
		: r(0), g(0), b(0), a(0) {}
	Color4uc(unsigned char same_intensity, unsigned char alpha = 255)
		: r(same_intensity), g(same_intensity), b(same_intensity), a(alpha) {}
	Color4uc(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
		: r(r), g(g), b(b), a(a) {}

	unsigned char r, g, b, a;

};
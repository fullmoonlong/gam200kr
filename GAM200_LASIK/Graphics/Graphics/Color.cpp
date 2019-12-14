/**************************************************************************************
 *	File Name        : Color.cpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : 
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Color4f.hpp"
#include "ColorInChar.hpp"

Color4f to4f(ColorInChar eight_bit_color)
{
	Color4f color4f;
	color4f.r = static_cast<float>(eight_bit_color.r) / static_cast<float>(255);
	color4f.g = static_cast<float>(eight_bit_color.g) / static_cast<float>(255);
	color4f.b = static_cast<float>(eight_bit_color.b) / static_cast<float>(255);
	color4f.a = static_cast<float>(eight_bit_color.a) / static_cast<float>(255);
	return color4f;
}
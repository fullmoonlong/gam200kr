/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Mesh.cpp
*	
*	Implement Mesh class
*	
*	2019/10/02
*/

#include "Mesh.h"
#include "Color.hpp"
#include <vec2.h>

void Mesh::AddPoint(MathLibrary::vec2 point) noexcept
{
	points.push_back(point);
}

void Mesh::AddColor(Color color) noexcept
{
	colors.push_back(color);
}

void Mesh::AddTextureCoordinate(MathLibrary::vec2 textureCoordinate) noexcept
{
	textureCoordinates.push_back(textureCoordinate);
}

MathLibrary::vec2 Mesh::GetPoint(int index) const noexcept
{
	return points[index];
}

Color Mesh::GetColor(int index) const noexcept
{
	return colors[index];
}

MathLibrary::vec2 Mesh::GetTextCoor(int index) const noexcept
{
	return textureCoordinates[index];
}

void Mesh::SetShapePattern(ShapePattern new_pattern) noexcept
{
	pattern = new_pattern;
}

ShapePattern Mesh::GetShapePattern() const noexcept
{
	return pattern;
}

size_t Mesh::GetPointsCount() const noexcept
{
	return points.size();
}

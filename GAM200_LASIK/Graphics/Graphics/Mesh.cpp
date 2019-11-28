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
#include "Math/Angle.hpp"

void Mesh::AddPoint(vec2<float> point)
{
	points.push_back(point);
}

void Mesh::AddPoint(float x, float y)
{
	points.push_back({ x, y });
}


void Mesh::AddColor(Color4f color)
{
	colors.push_back(color);
}

void Mesh::AddTextureCoordinate(vec2<float> texture_coordinate)
{
	textureCoordinates.push_back(texture_coordinate);
}

void Mesh::AddTextureCoordinate(float u, float v)
{
	textureCoordinates.push_back({ u, v });
}


void Mesh::SetShapePattern(ShapePattern new_pattern) noexcept
{
	pattern = new_pattern;
}

vec2<float> Mesh::GetPoint(int index) const noexcept
{
	return points[index];
}

Color4f Mesh::GetColor(int index) const noexcept
{
	return colors[index];
}

vec2<float> Mesh::GetTextureCoordinate(int index) const noexcept
{
	return textureCoordinates[index];
}

ShapePattern Mesh::GetShapePattern() const noexcept
{
	return pattern;
}

size_t Mesh::GetPointsCount() const noexcept
{
	return points.size();
}

Mesh MESH::create_ellipse(float rx, float ry, int pointsNum, Color4f color)
{
	Mesh circle;
	
	circle.SetShapePattern(ShapePattern::TriangleFan);
	const float angle = ANGLE::two_pi / static_cast<float>(pointsNum);

	for (int i = 0; i <= pointsNum; ++i)
	{
		circle.AddPoint({ rx * static_cast<float>(cos((float)i * angle)),
						ry * static_cast<float>(sin((float)i * angle)) });
		circle.AddColor(color);
	}

	return circle;
}

Mesh MESH::create_rectangle(float xPos, float yPos, float width, float height, Color4f color)
{
	Mesh rectangle;

	rectangle.SetShapePattern(ShapePattern::TriangleFan);

	float xHalf = width / 2.0f;
	float yHalf = height / 2.0f;
	
	rectangle.AddPoint({ -xHalf + xPos, -yHalf + yPos });
	rectangle.AddPoint({ -xHalf + xPos, yHalf + yPos });
	rectangle.AddPoint({ xHalf + xPos, yHalf + yPos});
	rectangle.AddPoint({ xHalf + xPos, -yHalf + yPos });
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddTextureCoordinate({ 0.f, 0.f });
	rectangle.AddTextureCoordinate({ 0.f, 1.f });
	rectangle.AddTextureCoordinate({ 1.f, 1.f });
	rectangle.AddTextureCoordinate({ 1.f, 0.f });

	return rectangle;
}

Mesh MESH::create_quad(vec2<float> p1, vec2<float> p2, vec2<float> p3, vec2<float> p4, Color4f color)
{
	Mesh quad;
	quad.SetShapePattern(ShapePattern::Quads);
	quad.AddPoint(p1);
	quad.AddPoint(p2);
	quad.AddPoint(p3);
	quad.AddPoint(p4);
	quad.AddColor(color);
	quad.AddColor(color);
	quad.AddColor(color);
	quad.AddColor(color);
	// maybe texture coordinate
	return quad;
}

Mesh MESH::create_line(vec2<float> p1, vec2<float> p2, Color4f color)
{
	Mesh line;
	line.SetShapePattern(ShapePattern::Line);
	line.AddPoint(p1);
	line.AddPoint(p2);
	line.AddColor(color);
	line.AddColor(color);
	return line;
}

Mesh MESH::create_triangle(vec2<float> p1, vec2<float> p2, vec2<float> p3, Color4f color)
{
	Mesh triangle;
	triangle.SetShapePattern(ShapePattern::Triangles);
	triangle.AddPoint(p1);
	triangle.AddPoint(p2);
	triangle.AddPoint(p3);
	triangle.AddColor(color);
	triangle.AddColor(color);
	triangle.AddColor(color);
	return triangle;
}

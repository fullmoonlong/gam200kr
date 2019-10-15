/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Mesh.cpp
*	
*	Implement Mesh class
*	
*	2019/10/02
*/

#include <graphic/Mesh.h>
#include <math/Angle.hpp>

void Mesh::AddPoint(Math::vec2<float> point) noexcept
{
	points.push_back(point);
}

void Mesh::AddColor(Color4f color) noexcept
{
	colors.push_back(color);
}

void Mesh::AddTextureCoordinate(Math::vec2<float> textureCoordinate) noexcept
{
	textureCoordinates.push_back(textureCoordinate);
}

Math::vec2<float> Mesh::GetPoint(int index) const noexcept
{
	return points[index];
}

Color4f Mesh::GetColor(int index) const noexcept
{
	return colors[index];
}

Math::vec2<float> Mesh::GetTextureCoordinate(int index) const noexcept
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

Mesh MESH::draw_ellipse(float rx, float ry, int pointsNum, Color4f /*color*/)
{
	Mesh circle;
	
	circle.SetShapePattern(ShapePattern::TriangleFan);
	const float angle = Angle::TWO_PI / (float)pointsNum;
	circle.AddPoint({ 0.0f,0.0f });	// Initial point
	//circle.AddColor(color);			// Color of initial point

	for (int i = 0; i <= pointsNum; i++)
	{
		circle.AddPoint({ rx * (float)cos((float)i * angle), ry * (float)sin((float)i * angle) });
		//circle.AddColor(color);
	}

	return circle;
}

Mesh MESH::draw_rectangle(float width, float height, Color4f color)
{
	Mesh rectangle;

	rectangle.SetShapePattern(ShapePattern::TriangleFan);

	float xHalf = width / 2.0f;
	float yHalf = height / 2.0f;
	
	rectangle.AddPoint({ -xHalf, -yHalf });
	rectangle.AddPoint({ -xHalf, yHalf });
	rectangle.AddPoint({ xHalf, yHalf });
	rectangle.AddPoint({ xHalf, -yHalf });
	rectangle.AddPoint({ -xHalf, -yHalf });
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddColor(color);
	rectangle.AddTextureCoordinate({ 0, 1 });
	rectangle.AddTextureCoordinate({ 0, 0 });
	rectangle.AddTextureCoordinate({ 1, 0 });
	rectangle.AddTextureCoordinate({ 1, 1 });
	rectangle.AddTextureCoordinate({ 0, 1 });

	return rectangle;
}

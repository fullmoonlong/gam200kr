/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Mesh.h
*	
*	Header of Mesh
*	
*	2019/10/02
*/

#pragma once
#include <vector>
#include "Color4f.hpp"
#include <vec2.hpp>

enum class ShapePattern
{
	Triangle,
	TriangleStrip,
	TriangleFan
};

class [[nodiscard]] Mesh
{
public:
	void AddPoint(Math::vec2<float> point) noexcept;
	void AddColor(Color4f color) noexcept;
	void AddTextureCoordinate(Math::vec2<float> textureCoordinate) noexcept;

	Math::vec2<float> GetPoint(int index) const noexcept;
	Color4f GetColor(int index) const noexcept;
	Math::vec2<float> GetTextureCoordinate(int index) const noexcept;

	void SetShapePattern(ShapePattern new_pattern) noexcept;
	ShapePattern GetShapePattern() const noexcept;

	size_t GetPointsCount() const noexcept;

private:
	std::vector<Math::vec2<float>> points;
	std::vector<Color4f> colors;
	std::vector<Math::vec2<float>> textureCoordinates;
	ShapePattern pattern = ShapePattern::Triangle;
	
};

namespace MESH
{
	Mesh draw_ellipse(float rx, float ry, int pointsNum, Color4f color);
	Mesh draw_rectangle(float width, float height, Color4f color);
	//void draw_line(MathLibrary::vec2, MathLibrary::vec2, MathLibrary::vec3 color);
}

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

namespace MathLibrary {
	class vec2;
}

class Color;

enum class ShapePattern
{
	Triangle,
	TriangleStrip,
	TriangleFan
};


class [[nodiscard]] Mesh
{
public:
	void AddPoint(MathLibrary::vec2 point) noexcept;
	void AddColor(Color color) noexcept;
	void AddTextureCoordinate(MathLibrary::vec2 textureCoordinate) noexcept;

	MathLibrary::vec2 GetPoint(int index) const noexcept;
	Color GetColor(int index) const noexcept;
	MathLibrary::vec2 GetTextCoor(int index) const noexcept;

	void SetShapePattern(ShapePattern new_pattern) noexcept;
	ShapePattern GetShapePattern() const noexcept;

	size_t GetPointsCount() const noexcept;

private:
	std::vector<MathLibrary::vec2> points;
	std::vector<Color> colors;
	std::vector<MathLibrary::vec2> textureCoordinates;
	ShapePattern pattern = ShapePattern::Triangle;
	
};

namespace MESH
{
	//void draw_ellipse(int rx, int ry, int pointsNum, MathLibrary::vec3 color);
	//void draw_rectangle(int width, int height, MathLibrary::vec3 color);
	//void draw_line(MathLibrary::vec2, MathLibrary::vec2, MathLibrary::vec3 color);
}

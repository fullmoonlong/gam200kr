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
#include "vec2.hpp"
#include "Color4f.hpp"

enum class ShapePattern
{
	Line,
	Triangles,
	TriangleStrip,
	TriangleFan,
	Quads
};

class [[nodiscard]]Mesh
{
public:
	void AddPoint(vec2<float> point);
	void AddPoint(float x, float y);
	void AddColor(Color4f color);
	void AddTextureCoordinate(vec2<float> texture_coordinate);
	void AddTextureCoordinate(float u, float v);
	void SetShapePattern(ShapePattern new_pattern) noexcept;

	vec2<float> GetPoint(int index) const noexcept;
	Color4f GetColor(int index) const noexcept;
	vec2<float> GetTextureCoordinate(int index) const noexcept;
	ShapePattern GetShapePattern() const noexcept;

	size_t GetPointsCount() const noexcept;
private:
	std::vector<vec2<float>> points;
	std::vector<Color4f> colors;
	std::vector<vec2<float>> textureCoordinates;
	ShapePattern pattern = ShapePattern::Triangles;
};

namespace MESH
{
	Mesh create_ellipse(float rx, float ry, int pointsNum, Color4f color);
	Mesh create_rectangle(float xPos, float yPos, float width, float height, Color4f color);
	Mesh create_quad(vec2<float> p1, vec2<float> p2, vec2<float> p3, vec2<float> p4, Color4f color);
	Mesh create_line(vec2<float> p1, vec2<float> p2, Color4f color);
};

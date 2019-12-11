/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: ShapeDrawingDemo.cpp
 *	
 *	Solar System in 2D
 *	
 *	Dec.03 2019
 *******************************************************/

#pragma once
#include "Demo.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Texture.hpp"
#include "Transform.hpp"

class SolarSystemDemo : public Demo
{
public:
	explicit SolarSystemDemo(Window& window) : Demo(window) { Initialize(); }

	struct Orb
	{
		Mesh mesh;
		Vertices vertices;
		Transform transform;
		Texture texture;
	};

	void Initialize() override final;
	void Update(float dt) override final;
	void ShutDown() override final;

	void ResetCamera() override final;

	void HandleResizeEvent(const int& new_width, const int& new_height) override;
	void HandleKeyPress(KeyboardButton button) override;
	void HandleKeyRelease(KeyboardButton button) override;
	void HandleFocusEvent(int focus) override;
	void HandleScrollEvent(float scroll_amount) override;
private:

	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Shader shader;

	Orb sun;
	Orb jupiter;
	Orb ganymede;
	Orb europa;
};

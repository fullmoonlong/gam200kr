/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: TextureDrawingDemo.hpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.29 2019
 *******************************************************/

#pragma once
#include "Demo.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Texture.hpp"
#include "Transform.hpp"

class TextureDrawingDemo : public Demo
{
public:
	explicit TextureDrawingDemo(Window& window) : Demo(window) { Initialize(); }
	void Initialize() override final;
	void Update() override final;
	void ShutDown() override final;

	void ResetCamera() override final;

	void HandleResizeEvent(const int& new_width, const int& new_height) override final;
	//void HandleKeyPress(KeyboardButton button) override;
	//void HandleKeyRelease(KeyboardButton button) override;
	void HandleFocusEvent(int focus) override;
private:
	Shader shader;

	Mesh mesh;
	Vertices vertices;
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Texture texture;
	Transform transform;
};

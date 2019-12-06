/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: TextureDrawingDemo.hpp
 *	
 *	Simple Texture Drawing Demo
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
#include "Animation.hpp"

class TextureDrawingDemo : public Demo
{
public:
	explicit TextureDrawingDemo(Window& window) : Demo(window) { Initialize(); }
	void Initialize() override final;
	void Update(float dt) override final;
	void ShutDown() override final;

	void ResetCamera() override final;

	void HandleResizeEvent(const int& new_width, const int& new_height) override final;
	void HandleFocusEvent(int focus) override final;
private:
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Shader shader;
	Mesh mesh;
	Vertices vertices;
	Texture pepe;
	Transform transform;
};

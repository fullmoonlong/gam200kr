/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: AnimationDemo.hpp
 *	
 *	Animation Displaying
 *	
 *	Dec.03 2019
 *******************************************************/

#pragma once
#include "Demo.hpp"
#include "Animation.hpp"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Texture.hpp"
#include "Transform.hpp"

class AnimationDemo : public Demo
{
public:
	explicit AnimationDemo(Window& window) : Demo(window) { Initialize(); }
	void Initialize() override final;
	void Update(float dt) override final;
	void ShutDown() override final;

	void ResetCamera() override final;

	void HandleResizeEvent(const int& new_width, const int& new_height) override final;
	void HandleFocusEvent(int focus) override;
private:
	Shader shader;
	Mesh mesh;
	Vertices vertices;
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Texture texture;
	Transform transform;
	Animation explosion;
};


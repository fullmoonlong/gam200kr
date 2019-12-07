/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: TransformParentDemo.hpp
 *	
 *	Transform Set Parent Test
 *	
 *	Dec.07 2019
 *******************************************************/

#pragma once
#include "Demo.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "VerticesDescription.h"
#include "Transform.hpp"
#include "Draw.hpp"

class TransformParentDemo : public Demo
{
public:
	explicit TransformParentDemo(Window& window) : Demo(window) { Initialize(); }

	void Initialize() override final;
	void Update(float dt) override final;
	void ShutDown() override final;

	void ResetCamera() override final;

	void HandleResizeEvent(const int& new_width, const int& new_height) override final;
	void HandleMousePositionEvent(float xpos, float ypos) override final;
	void HandleMouseEvent(MouseButton button) override;
private:
	bool isClicked = false;
	mat3<float> cameraToNDC;
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Shader shader;

	vec2<float> mousePosition;

	Material sword1;
	Transform sword1Transform;

	float slashRotation = 0.0f;
	Material slash1;
	Transform slash1Transform;

	Material slash2;
	Transform slash2Transform;
};


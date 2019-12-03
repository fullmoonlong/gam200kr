/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: ShapeDrawingDemo.cpp
 *	
 *	Solar System in 2D
 *	
 *	Dec.03 2019
 *******************************************************/

#include <iostream>
#include "SolarSystemDemo.hpp"
#include "Draw.hpp"
#include "PATH.hpp"

const std::filesystem::path& sun_jpg = "../assets/sun.jpg";
const std::filesystem::path& jupiter_png = "../assets/jupiter.png";

void SolarSystemDemo::Initialize()
{
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	
	Mesh rectangle = MESH::create_rectangle({ 0.0f }, { 100.0f }, { 0.96f, 0.6f, 0.0f, 1.0f });
	sun.mesh = rectangle;
	sun.vertices.InitializeWithMeshAndLayout(sun.mesh, layout);
	sun.texture.LoadFromPath(sun_jpg);
	sun.transform.SetTranslation({ -1000.0f, 0.0f });
	sun.transform.SetScale({ 20.0f });

	jupiter.mesh = rectangle;
	jupiter.vertices.InitializeWithMeshAndLayout(jupiter.mesh, layout);
	jupiter.texture.LoadFromPath(jupiter_png);

	view.SetViewSize(width, height);
}

void SolarSystemDemo::Update(float dt)
{
	static float rotation = 0.0f;
	rotation += dt / 8.f;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	const mat3<float> sunNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * sun.transform.GetModelToWorld();
	Draw::draw({ shader, sun.vertices, sunNDC, sun.texture });

	const mat3<float> jupiterNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * jupiter.transform.GetModelToWorld();
	Draw::draw({ shader, jupiter.vertices, jupiterNDC, jupiter.texture });

	jupiter.transform.SetTranslation({ 1000.0f * cos(rotation), 1000.0f * sin(rotation) });
	jupiter.transform.SetRotation(cos(rotation));

	//sun.transform.SetRotation(rotation);

	Draw::FinishDrawing();
}

void SolarSystemDemo::ShutDown()
{
}

void SolarSystemDemo::ResetCamera()
{
	camera.ResetUp();
}

void SolarSystemDemo::HandleResizeEvent(const int& new_width, const int& new_height)
{
	Demo::HandleResizeEvent(new_width, new_height);
}

void SolarSystemDemo::HandleKeyPress(KeyboardButton button)
{
	button;
}

void SolarSystemDemo::HandleKeyRelease(KeyboardButton button)
{
	button;
}

void SolarSystemDemo::HandleFocusEvent(int focus)
{
	if (focus != GLFW_TRUE)
	{
		Draw::StartDrawing();
		Draw::FinishDrawing();
	}
}

void SolarSystemDemo::HandleScrollEvent(float scroll_amount)
{
	//const float zoomSpeed = .05f;
	//float newZoom = view.GetZoom() + (scroll_amount * zoomSpeed);
	//newZoom = std::clamp(newZoom, 0.5f, 2.0f);
	//view.SetZoom(newZoom);
	Demo::HandleScrollEvent(scroll_amount);
}

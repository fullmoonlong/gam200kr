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
const std::filesystem::path& ganymede_png = "../assets/ganymede.png";
const std::filesystem::path& europa_png = "../assets/europa.png";

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

	ganymede.mesh = rectangle;
	ganymede.vertices.InitializeWithMeshAndLayout(ganymede.mesh, layout);
	ganymede.texture.LoadFromPath(ganymede_png);
	ganymede.transform.SetTranslation({ 100.0f, 0.0f });
	ganymede.transform.SetScale({ 1 / 5.f });
	ganymede.transform.SetParent(&jupiter.transform);

	europa.mesh = rectangle;
	europa.vertices.InitializeWithMeshAndLayout(europa.mesh, layout);
	europa.texture.LoadFromPath(europa_png);
	europa.transform.SetTranslation({ -100.0f, 0.0f });
	europa.transform.SetScale({ 1 / 5.f });
	europa.transform.SetParent(&jupiter.transform);
	
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

	const mat3<float> ganymedeNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * ganymede.transform.GetModelToWorld();
	Draw::draw({ shader, ganymede.vertices, ganymedeNDC, ganymede.texture });

	const mat3<float> europaNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * europa.transform.GetModelToWorld();
	Draw::draw({ shader, europa.vertices, europaNDC, europa.texture });
	
	jupiter.transform.SetTranslation({ 1500.0f * cos(rotation) - 1000.0f, 1500.0f * sin(rotation) });
	jupiter.transform.SetRotation(rotation * 5.f);

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
	Demo::HandleScrollEvent(scroll_amount);
}

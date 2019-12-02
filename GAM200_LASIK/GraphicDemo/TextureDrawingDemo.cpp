/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: TextureDrawingDemo.cpp
 *	
 *	Graphic demo main file
 *	
 *	Nov.29 2019
 *******************************************************/

#include "TextureDrawingDemo.hpp"
#include "Draw.hpp"
#include "PATH.hpp"

void TextureDrawingDemo::Initialize()
{
	shader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	mesh = MESH::create_rectangle({ 0.0f }, { 100.0f, 100.0f }, { 0.0f });
	vertices.InitializeWithMeshAndLayout(mesh, layout);
	pepe.LoadFromPath(PATH::pepe);
	transform.SetScale({ 7.5f });

	view.SetViewSize(width, height);
}

void TextureDrawingDemo::Update(float /*dt*/)
{
	Draw::StartDrawing();

	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	Draw::draw(shader, { vertices, pepe });
	shader.SendUniformVariable("ndc", ndc);
		
	Draw::FinishDrawing();
}

void TextureDrawingDemo::ShutDown()
{
}

void TextureDrawingDemo::ResetCamera()
{
	camera.ResetUp();
}

void TextureDrawingDemo::HandleResizeEvent(const int& new_width, const int& new_height)
{
	Demo::HandleResizeEvent(new_width, new_height);
}

void TextureDrawingDemo::HandleFocusEvent(int focus)
{
	if (focus != GLFW_TRUE)
	{
		Draw::StartDrawing();
		Draw::FinishDrawing();
	}
}
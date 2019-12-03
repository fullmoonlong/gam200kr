/********************************************************
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: AnimationDemo.cpp
 *	
 *	Animation Displaying
 *	
 *	Dec.03 2019
 *******************************************************/

#include "AnimationDemo.hpp"
#include "Draw.hpp"
#include "PATH.hpp"

const std::filesystem::path& explosion_path = "../assets/explosion.png";

void AnimationDemo::Initialize()
{
	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);

	mesh = MESH::create_rectangle({ 0.0f }, { 1.0f }, { 0.0f });
	vertices.InitializeWithMeshAndLayout(mesh, layout);
	texture.LoadFromPath(explosion_path);
	
	explosion.Initialize({ 15, 5.0f }, shader);
}

void AnimationDemo::Update(float dt)
{
	Draw::StartDrawing();

	explosion.Animate(dt);
	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	Draw::draw({ shader, vertices, ndc, texture });

	Draw::FinishDrawing();
}

void AnimationDemo::ShutDown()
{
}

void AnimationDemo::ResetCamera()
{
	camera.ResetUp();
}

void AnimationDemo::HandleResizeEvent(const int& new_width, const int& new_height)
{
	Demo::HandleResizeEvent(new_width, new_height);
}

void AnimationDemo::HandleFocusEvent(int /*focus*/)
{
}

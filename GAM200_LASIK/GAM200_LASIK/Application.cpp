/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "PATH.hpp"
#include "VerticesDescription.h"
#include "Image.hpp"
#include "Text.hpp"
#include "Application.h"

Application::Application()
{
	Initialize();
	isRunning = true;
}

void Application::Initialize()
{
	window.CanCreateWindow(800, 600, this,"Lasik");

	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);	//shaders for animation
	fontShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	
	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	const Color4f color2{ 0.5f, 0.5f, 0.3f, 1.0f };
	const float starting_x = 300.0f;
	const float starting_y = 0.0f;
	const float objectWidth = 50.0f;
	const float objectHeight = 50.0f;
	rectangle = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
	rectangle2 = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color2);
	
	float aLeft = 0.0f / 256;
	float aBottom = 1.0f - 20.0f / 256;
	float aTop = aBottom + 20.0f / 256;
	float aRight = 19.0f / 256;
	textMesh.SetShapePattern(ShapePattern::Triangle);
	textMesh.AddPoint(-0.5f, 0.5f);
	textMesh.AddPoint(0.5f, 0.5f);
	textMesh.AddPoint(-0.5f, -0.5f);
	textMesh.AddTextureCoordinate(aLeft, aTop);
	textMesh.AddTextureCoordinate(aRight, aTop);
	textMesh.AddTextureCoordinate(aLeft, aBottom);

	float iLeft = 
	textMesh.AddPoint(0.5f, 0.5f);
	textMesh.AddPoint(-0.5f, -0.5f);
	textMesh.AddPoint(0.5f, -0.5f);
	textMesh.AddTextureCoordinate({ aRight, aTop });
	textMesh.AddTextureCoordinate({ aLeft, aBottom });
	textMesh.AddTextureCoordinate({ aRight, aBottom });

	textMesh.AddPoint(0.5f, 0.5f);
	textMesh.AddPoint(1.5f, 0.5f);
	textMesh.AddPoint(0.5f, 0.5f);
	textMesh.AddTextureCoordinate()
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	vertices2.InitializeWithMeshAndLayout(rectangle2, layout);
	textVertices.InitializeWithMeshAndLayout(textMesh, layout);

	Image image(PATH::kevin_move);
	Image image2(PATH::kevin_attack);
	
	Texture t1(image);
	Texture t2(image2);
	
	material.vertices = vertices;
	material.mesh = rectangle;
	material.texture = t1;
	material2.vertices = vertices2;
	material2.mesh = rectangle2;
	material2.texture = t2;

	fontTexture.LoadFromPath(PATH::bitmapfont_png);

	animation.Initialize(image, rectangle, 8, shader);
	animation2.Initialize(image2, rectangle2, 7, shader);
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera
	
	object.Initialize({ starting_x, starting_y }, objectWidth, objectHeight);
	object.speed.x = -150.0f;
	object2.Initialize({-300.0f, 0.0f }, objectWidth, objectHeight);
	object2.speed.x = 150.0f;

	lasik.Initialize({ 0.0f, 0.0f }, 30.0f, 30.0f);
	

	bitmapFont.LoadFromFile(PATH::bitmapfont_fnt);
}

void Application::Update()
{
	clock.UpdateClock();

	//Object moving
	//object.Update(deltaTime);
	//object2.Update(deltaTime);
	//
	//if (object.GetXposition() < 0.0f)
	//{
	//	animation.ChangeAnimation(PATH::kevin_attack, 7);
	//	object.speed.x = 0.0f;
	//}
	//Object moving


	//Draw
	draw.StartDrawing();


	Text text(L"LASIK", bitmapFont);
	//for (const auto& vertices_texture_pair : text.GetVerticesWithMatchingTextures())
	//{
	//	const Vertices& text_vertices = *vertices_texture_pair.first;
	//	const Texture*  text_texture  = vertices_texture_pair.second;
	//	//	textMaterial.textureUniforms.insert_or_assign(SHADER::Uniform_Texture, texture_uniform{text_texture});
	//	//	//GL::draw(text_vertices, textMaterial);
	//	Material fontMaterial;
	//	Transform fontTransform;
	//	fontTransform.SetScale({ 100.0f, 100.0f });
	//	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * fontTransform.GetModelToWorld();
	//	fontShader.SendUniformVariable("ndc", ndc);
	//	fontMaterial.vertices = text_vertices;
	//	//glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, text_texture->GetTexturehandle());
	//	draw.draw(fontShader, fontMaterial);
	//}

	const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object.transform.GetModelToWorld();
	const mat3<float> ndc2 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object2.transform.GetModelToWorld();
	const mat3<float> ndc_font = view.GetCameraToNDCTransform() * camera.WorldToCamera() * lasik.transform.GetModelToWorld();
	

	animation.Animate(deltaTime);
	shader.SendUniformVariable("ndc", ndc);
	Draw::draw(shader, material);

	animation2.Animate(deltaTime);
	shader.SendUniformVariable("ndc", ndc2);
	Draw::draw(shader, material2);

	Draw::draw(fontShader, { textVertices, fontTexture, textMesh });
	fontShader.SendUniformVariable("ndc", ndc_font);

	draw.Finish();
	//Draw

	
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//Transform

	++frameCount;
	static int time = 0;
	if (clock.timePassed >= 1.0f)
	{
		++time;
		std::cout << time << std::endl;
		std::cout << frameCount << std::endl;
		clock.timePassed -= 1.0f;
		frameCount = 0;
	}
	deltaTime = clock.GetTimeFromLastUpdate();
	
	window.SwapBuffers();
	window.PollEvents();
}

void Application::ShutDown()
{
	isRunning = false;
	if ((bool)glfwWindowShouldClose(window.window) != true)
	{
		glfwSetWindowShouldClose(window.window, GLFW_FALSE);
	}
}

void Application::HandleKeyPress(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Escape:
		this->ShutDown();
		break;
	case KeyboardButtons::F:
		window.ToggleFullScreen();
		break;
	case KeyboardButtons::V:
		if (window.IsVSyncOn() == false)
		{
			window.ToggleVSync(true);
			break;
		}
		window.ToggleVSync(false);
		break;
	case KeyboardButtons::W:
		//pressDirection.y += 
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? -2.0f : 2.0f;
		object.speed.y = 0.8f;
		break;
	case KeyboardButtons::S:
		//pressDirection.y +=
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 2.0f : -2.0f;
		object.speed.y = -0.8f;
		break;
	case KeyboardButtons::A:
		//pressDirection.x -= 2.0f;
		object.speed.x = -0.8f;
		break;
	case KeyboardButtons::D:
		//pressDirection.x += 2.0f;
		object.speed.x = 0.8f;
		break;
	case KeyboardButtons::Z:
		cameraAngle += 0.025f;
		break;
	case KeyboardButtons::X:
		cameraAngle -= 0.025f;
		break;
	default:;
	}
}

void Application::HandleKeyRelease(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::W:
		pressDirection.y = 0;
		object.speed.y = 0.f;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		object.speed.y = 0.f;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		object.speed.x = 0.f;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		object.speed.x = 0.f;
		break;
	case KeyboardButtons::Z:
		cameraAngle = 0.0f;
		break;
	case KeyboardButtons::X:
		cameraAngle = 0.0f;
		break;
	default:;
	}
}

void Application::HandleMouseEvent(MouseButtons button)
{
	switch (button)
	{
	case MouseButtons::LEFT_PRESS:
	{
		//mouse check
		if (object.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
		{
			object.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButtons::LEFT_RELEASE:
		object.isMouseCollide = false;
		break;
	}
}

void Application::HandleResizeEvent(const int& new_width, const int& new_height)
{
	window.SetWindowWidth(new_width);
	window.SetWindowHeight(new_height);

	//camera
	view.SetViewSize(new_width, new_height);
	view.SetZoom(zoom);
	//camera
}

void Application::HandleScrollEvent(float scroll_amount)
{
	zoom = view.GetZoom() + (scroll_amount * 0.05f);
	zoom = std::clamp(zoom, 0.1f, 2.0f);
	view.SetZoom(zoom);
}

void Application::HandleMousePositionEvent(float xpos, float ypos)
{
	//vec2<float> newMousePosition{ xpos, ypos };
	mousePosition = { xpos, ypos };
}

void Application::HandleWindowClose()
{
	ShutDown();
}

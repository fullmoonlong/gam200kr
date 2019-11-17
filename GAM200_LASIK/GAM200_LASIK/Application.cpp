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
	const float width = 50.0f;
	const float height = 50.0f;
	rectangle = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
	rectangle2 = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color2);
	textMesh = MESH::create_rectangle(0.0f, 0.0f, 1.0f, 1.0f, color);
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	vertices2.InitializeWithMeshAndLayout(rectangle2, layout);
	textVertices.InitializeWithMeshAndLayout(textMesh, layout);

	material.vertices = vertices;
	material.mesh = rectangle;
	material2.vertices = vertices2;
	material2.mesh = rectangle2;
	
	Image image(PATH::kevin_move);
	Image image2(PATH::kevin_attack);

	fontTexture.LoadFromPath(PATH::bitmapfont_png);

	animation.Initialize(image, rectangle, 8, shader);
	animation2.Initialize(image2, rectangle2, 7, shader);
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera
	
	object.Initialize({ starting_x, starting_y }, width, height);
	object.speed.x = -150.0f;
	object2.Initialize({-300.0f, 0.0f }, width, height);
	object2.speed.x = 150.0f;

	lasik.Initialize({ 0.0f, 0.0f }, 50.0f, 50.0f);
	

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
	//Mesh textMesh;
	//textMesh.SetShapePattern(ShapePattern::Triangle);

	//float left = 0 + -1;
	//float right = left + 19;
	//float bottom = -1 * (6 + 20) + 32 + 0;
	//float top = bottom + 20;

	//float textureLeft = 0.0f / 256;
	//float textureTop = 0.0f / 256;
	//float textureRight = 19.0f / 256;
	//float textureBottom = 20.0f / 256;
	
	//textMesh.AddPoint({ left, top });
	//textMesh.AddPoint({ right, top });
	//textMesh.AddPoint({ left, bottom });
	//textMesh.AddTextureCoordinate({ textureLeft, textureTop });
	//textMesh.AddTextureCoordinate({ textureRight, textureTop });
	//textMesh.AddTextureCoordinate({ textureLeft, textureBottom });

	//textMesh.AddPoint({ right, top });
	//textMesh.AddPoint({ left, bottom });
	//textMesh.AddPoint({ right, bottom });
	//textMesh.AddTextureCoordinate({ textureRight, textureTop });
	//textMesh.AddTextureCoordinate({ textureLeft, textureBottom });
	//textMesh.AddTextureCoordinate({ textureRight, textureBottom });
	//textMesh.AddPoint({ -50.0f, 50.0f });
	//textMesh.AddPoint({ 50.0f, 50.0f });
	//textMesh.AddPoint({ -50.0f, -50.0f });
	//textMesh.AddTextureCoordinate({ 0.0f, 0.0f });
	//textMesh.AddTextureCoordinate({ 1.0f, 0.0f });
	//textMesh.AddTextureCoordinate({ 0.0f, 1.0f });

	//textMesh.AddPoint({ 50.0f, 50.0f });
	//textMesh.AddPoint({ -50.0f, -50.0f });
	//textMesh.AddPoint({ 50.0f, -50.0f });
	//textMesh.AddTextureCoordinate({ 1.0f, 0.0f });
	//textMesh.AddTextureCoordinate({ 0.0f, 1.0f });
	//textMesh.AddTextureCoordinate({ 1.0f, 1.0f });

	//Vertices textVertices;
	//const VerticesDescription textLayout = { VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	//textVertices.InitializeWithMeshAndLayout(textMesh, textLayout);

	//Image fontImage(PATH::bitmapfont_png);
	//Texture fontTexture(fontImage);
	glBindTexture(GL_TEXTURE_2D, fontTexture.GetTexturehandle());
	mat3<float> ndc_font = view.GetCameraToNDCTransform() * camera.WorldToCamera() * lasik.transform.GetModelToWorld();
	fontShader.SendUniformVariable("ndc", ndc_font);
	Vertices::SelectVAO(textVertices);
	Shader::UseShader(fontShader);
	//glBindBuffer(GL_ARRAY_BUFFER, material.vertices.VBO);
	glDrawArrays(material.vertices.GetPattern(), 0, (int)material.mesh.GetPointsCount());
	

	//draw.draw(shader, material);
	//animation.Animate(deltaTime);
	//const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object.transform.GetModelToWorld();
	//shader.SendUniformVariable("ndc", ndc);

	//draw.draw(shader, material2);
	//animation2.Animate(deltaTime);
	//const mat3<float> ndc2 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * object2.transform.GetModelToWorld();
	//shader.SendUniformVariable("ndc", ndc2);
	
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
	glfwSetWindowShouldClose(window.window, GLFW_TRUE);
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


void Application::HandleResizeEvent(const int& width, const int& height)
{
	window.SetWindowWidth(width);
	window.SetWindowHeight(height);
	glfwSetWindowSize(window.window, width, height);
	//camera
	view.SetViewSize(width, height);
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

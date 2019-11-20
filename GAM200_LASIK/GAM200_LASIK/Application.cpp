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
#include "ComponentTest.h"
#include "GetInput.hpp"
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

	textMesh.AddPoint(0.5f, 0.5f);
	textMesh.AddPoint(-0.5f, -0.5f);
	textMesh.AddPoint(0.5f, -0.5f);
	textMesh.AddTextureCoordinate(aRight, aTop);
	textMesh.AddTextureCoordinate(aLeft, aBottom);
	textMesh.AddTextureCoordinate(aRight, aBottom);
	float kLeft = 20.0f / 256;

	float kBottom = 1.0f - 20.0f / 256;
	float kRight = (20.0f + 18.0f) / 256;
	float kTop = kBottom + 20.0f / 256;
	textMesh.AddPoint(0.5f, 0.5f);
	textMesh.AddPoint(1.5f, 0.5f);
	textMesh.AddPoint(0.5f, -0.5f);
	textMesh.AddTextureCoordinate(kLeft, kTop);

	textMesh.AddTextureCoordinate(kLeft, kBottom);
	textMesh.AddTextureCoordinate(kRight, kTop);
	textMesh.AddPoint(1.5f, 0.5f);
	textMesh.AddPoint(0.5f, -0.5f);
	textMesh.AddPoint(1.5f, -0.5f);
	textMesh.AddTextureCoordinate(kRight, aTop);
	textMesh.AddTextureCoordinate(kLeft, aBottom);
	textMesh.AddTextureCoordinate(kRight, aBottom);
	
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	vertices.InitializeWithMeshAndLayout(rectangle, layout);
	vertices2.InitializeWithMeshAndLayout(rectangle2, layout);
	textVertices.InitializeWithMeshAndLayout(textMesh, layout);

	Image image2(PATH::kevin_attack);
	Image image(PATH::kevin_move);
	
	Texture t1(image);
	
	Texture t2(image2);
	material.vertices = vertices;
	material.mesh = rectangle;
	material.texture = t1;
	material2.vertices = vertices2;
	material2.mesh = rectangle2;
	material2.texture = t2;


	animation.Initialize(image, rectangle, 8, shader);
	fontTexture.LoadFromPath(PATH::bitmapfont_png);
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

	backgroundShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	backgroundMesh = MESH::create_rectangle(0.0f, 0.0f, 1.0f, 1.0f, color);
	backgroundVertices.InitializeWithMeshAndLayout(backgroundMesh, layout);
	backgroundTexture.LoadFromPath(PATH::background);
	background.transform.SetDepth(-0.5f);

	backgroundMaterial.mesh = backgroundMesh;
	backgroundMaterial.vertices = backgroundVertices;
	backgroundMaterial.texture = backgroundTexture;
	
	background.Initialize({ 0.0f, 0.0f }, 50.0f, 50.0f);

	//background
	image.LoadFrom(PATH::knight_move);
	mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
	vertices.InitializeWithMeshAndLayout(mesh, layout);

	material.vertices = vertices;
	material.mesh = mesh;

	//background

	//dynamic test
	proKevin = new Object();
	proKevin->Initialize("enemyPrototype.txt");
	proKevin->image.LoadFrom(PATH::kevin_move);

	proKevin->SetHealth(100);
	proKevin->SetDamage(15);
	vec2<float> a = {1, 0};
	proKevin->SetAttackRange(a);

	const Color4f color3{ 1.0f, 0.0f, 0.0f, 1.0f };

	proKevin->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color3);
	proKevin->vertices.InitializeWithMeshAndLayout(proKevin->mesh, layout);

	proKevin->material.vertices = proKevin->vertices;
	proKevin->material.mesh = proKevin->mesh;

	proKevin->animation.Initialize(proKevin->image, proKevin->mesh, 8, shader);
	proKevin->SetState(State::WALK);

	//knight
	knight = new Knight();
	knight->Initialize("knight.txt");
	knight->image.LoadFrom(PATH::knight_move);

	knight->SetHealth(knight->GetKnightHealth());
	knight->SetDamage(knight->GetKnightDamage());

	const Color4f color4{ 1.0f, 0.0f, 0.0f, 1.0f };

	knight->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color4);
	knight->vertices.InitializeWithMeshAndLayout(knight->mesh, layout);

	knight->material.vertices = knight->vertices;
	knight->material.mesh = knight->mesh;

	knight->animation.Initialize(knight->image, knight->mesh, 8, shader);
	knight->SetState(State::WALK);
	//knight

	//archer
	archer = new Archer();
	archer->Initialize("archer.txt");
	archer->image.LoadFrom(PATH::archer_move);

	archer->SetHealth(archer->GetArcherHealth());
	archer->SetDamage(archer->GetArcherDamage());
	archer->SetAttackRange(archer->GetArcherAttackRange());

	archer->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color4);
	archer->vertices.InitializeWithMeshAndLayout(archer->mesh, layout);

	archer->material.vertices = archer->vertices;
	archer->material.mesh = archer->mesh;

	archer->animation.Initialize(archer->image, archer->mesh, 8, shader);
	archer->SetState(State::WALK);
	//archer

	//magician
	magician = new Magician();
	magician->Initialize("wizard.txt");
	magician->image.LoadFrom(PATH::wizard_move);

	magician->SetHealth(magician->GetMagicianHealth());
	magician->SetDamage(magician->GetMagicianDamage());
	magician->SetAttackRange(magician->GetMagicianAttackRange());

	magician->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color4);
	magician->vertices.InitializeWithMeshAndLayout(magician->mesh, layout);

	magician->material.vertices = magician->vertices;
	magician->material.mesh = magician->mesh;

	magician->animation.Initialize(magician->image, magician->mesh, 8, shader);
	magician->SetState(State::WALK);
	//magician

	//sword
	swordAttack = new Object();
	swordAttack->Initialize("swordAttack.txt");

	swordAttack->SetDamage(knight->GetKnightDamage());

	swordAttack->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color4);
	swordAttack->vertices.InitializeWithMeshAndLayout(swordAttack->mesh, layout);

	swordAttack->material.vertices = swordAttack->vertices;
	swordAttack->material.mesh = swordAttack->mesh;
	//sword

	//fireball
	fireball = new Object();
	fireball->Initialize("fireball.txt");
	fireball->image.LoadFrom(PATH::fireball);

	fireball->SetDamage(magician->GetMagicianDamage());

	fireball->mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color4);
	fireball->vertices.InitializeWithMeshAndLayout(fireball->mesh, layout);

	fireball->material.vertices = fireball->vertices;
	fireball->material.mesh = fireball->mesh;

	fireball->animation.Initialize(fireball->image, fireball->mesh, 3, shader);
	fireball->SetState(State::WALK);
	//fireball

	//arrow
	arrow.Initialize("arrow.txt");
	arrow.image.LoadFrom(PATH::arrow);

	arrow.SetDamage(archer->GetArcherDamage());

	arrow.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color4);
	arrow.vertices.InitializeWithMeshAndLayout(arrow.mesh, layout);

	arrow.material.vertices = arrow.vertices;
	arrow.material.mesh = arrow.mesh;

	arrow.animation.Initialize(arrow.image, arrow.mesh, 1, shader);
	arrow.SetState(State::WALK);
	//arrow
	//dynamic test

	//test sound and make object
	SOUNDMANAGER->Initialize();
	SOUNDMANAGER->LoadFile("sound.mp3");
	SOUNDMANAGER->LoadFile("beep.wav");
	SOUNDMANAGER->LoadFile("hit.ogg");
	SOUNDMANAGER->PlaySound(1, 0);
	SOUNDMANAGER->SetSystemSoundVolume(0.5f);
	//test sound and make object

	//object.Initialize({ starting_x, starting_y }, width, height);
	//object.speed.x = -150.0f;
	//object2.Initialize({-300.0f, 0.0f }, width, height);
	//object2.speed.x = 150.0f;
}

void Application::Update()
{
	clock.UpdateClock();

	OBJECTFACTORY->Update();
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//Transform
	
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
	const mat3<float> ndcBackground = view.GetCameraToNDCTransform() * camera.WorldToCamera() * background.transform.GetModelToWorld();
	
	Draw::draw(backgroundShader, backgroundMaterial);
	shader.SendUniformVariable("ndc", ndcBackground);
	
	animation.Animate(deltaTime);
	shader.SendUniformVariable("ndc", ndc);
	Draw::draw(shader, material);

	animation2.Animate(deltaTime);
	shader.SendUniformVariable("ndc", ndc2);
	Draw::draw(shader, material2);

	Draw::draw(fontShader, { textVertices, fontTexture, textMesh });
	fontShader.SendUniformVariable("ndc", ndc_font);

	//dynamic test
	for (auto obj : OBJECTFACTORY->GetObjecteList())
	{
		if (obj.second != nullptr)
		{
			obj.second->Update(deltaTime);
			obj.second->ChangeUnitAnimation();
			obj.second->animation.Animate(deltaTime);
			const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->transform.GetModelToWorld();
			shader.SendUniformVariable("ndc", ndc);
			draw.draw(shader, obj.second->material);
		}
		
	}
	//dynamic test

	draw.Finish();
	//Draw

	++frameCount;
	static int time = 0;
	if (clock.timePassed >= 1.0f)
	{
		++time;
		std::cout << time << std::endl;
		std::cout << frameCount << std::endl;
		clock.timePassed -= 1.0f;
		frameCount = 0;
		OBJECTFACTORY->DamageTest(time); //test for damage

		//for (auto obj : OBJECTFACTORY->GetObjecteList())
		//{
		//	if (obj.second->GetName() == "Archer" && time % 2 == 0)
		//	{
		//		obj.second->GetComponent<TestComponent>()->Attack();
		//	}
		//}
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
		//object.speed.y = 0.8f;
		for (auto obj : OBJECTFACTORY->GetObjecteList())
		{
			if (obj.second->GetType() == UnitType::Enemy)
			{
				OBJECTFACTORY->Destroy(obj.second);
			}
		}
		break;
	case KeyboardButtons::S:
		//pressDirection.y +=
		//	(view.GetFrameOfReference() == FrameOfReference::LeftHanded_OriginTopLeft) ? 2.0f : -2.0f;
		//object.speed.y = -0.8f;
		for (auto obj : OBJECTFACTORY->GetObjecteList())
		{
			if (obj.second->GetType() == UnitType::Player)
			{
				OBJECTFACTORY->Destroy(obj.second);
			}
		}
		break;
	case KeyboardButtons::A:
		//pressDirection.x -= 2.0f;
		input.TakeAsInput();
		if (input.MatchStringWithInput() == 1)
		{
			OBJECTFACTORY->CopyObject(knight);
			SOUNDMANAGER->PlaySound(0, 1);
		}
		else if (input.MatchStringWithInput() == 2)
		{
			OBJECTFACTORY->CopyObject(archer);
			/*OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1)->AddComponent<TestComponent>();
			OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1)->GetComponent<TestComponent>()->object = OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1);
			OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1)->GetComponent<TestComponent>()->attack = &arrow;*/
			SOUNDMANAGER->PlaySound(0, 1);
		}
		else if (input.MatchStringWithInput() == 3)
		{
			OBJECTFACTORY->CopyObject(magician);
			SOUNDMANAGER->PlaySound(0, 1);
		}
		//object.speed.x = -0.8f;
		break;
	case KeyboardButtons::D:
		//pressDirection.x += 2.0f;
		SOUNDMANAGER->PlaySound(0, 1);
		OBJECTFACTORY->CopyObject(proKevin);
		//object.speed.x = 0.8f;
		break;
	case KeyboardButtons::Z:
		//cameraAngle += 0.025f;
		break;
	case KeyboardButtons::X:
		//cameraAngle -= 0.025f;
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
		//object.speed.y = 0.f;
		break;
	case KeyboardButtons::S:
		pressDirection.y = 0;
		//object.speed.y = 0.f;
		break;
	case KeyboardButtons::A:
		pressDirection.x = 0;
		//object.speed.x = 0.f;
		break;
	case KeyboardButtons::D:
		pressDirection.x = 0;
		//object.speed.x = 0.f;
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

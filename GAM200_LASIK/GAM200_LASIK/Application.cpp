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
	window.CanCreateWindow(1280, 720, this, "Lasik");

	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);	//shaders for animation
	fontShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	backgroundShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	const Color4f color{ 1.0f, 1.0f, 1.0f, 1.0f };
	const VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	const Mesh& rectangle = MESH::create_rectangle(0.0f, 0.0f, 1.0f, 1.0f, color);


	bitmapFont.LoadFromFile(PATH::bitmapfont_fnt);
	text.SetFont(bitmapFont);
	text.SetString(L"LASIK");
	textTransform.SetTranslation({ -300.0f, 0.0f });
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera

	//background
	backgroundShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	backgroundMesh.SetShapePattern(ShapePattern::TriangleFan);
	backgroundVertices.InitializeWithMeshAndLayout(rectangle, layout);
	backgroundTexture.LoadBackground();
	background.transform.SetScale({ 1280, 720 });
	//background
	
	// unit initialize
	{
		//kevin
		proKevin = new Object();
		proKevin->Initialize("enemyPrototype.txt");
		//proKevin->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		proKevin->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		proKevin->material.texture.LoadFromPath(PATH::kevin_move);
		proKevin->animation.Initialize(8, shader);

		proKevin->SetState(State::WALK);
		proKevin->SetHealth(100);
		proKevin->SetDamage(15);
		proKevin->SetAttackRange({ 1.0f, 0.0f });
		//kevin

		//knight
		knight = new Knight();
		knight->Initialize("knight.txt");
		//knight->material.mesh = MESH::create_rectangle(0.0f, 0.0f, 1.0f, 1.0f, color);
		knight->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		knight->material.texture.LoadFromPath(PATH::knight_move);
		knight->animation.Initialize(8, shader);

		knight->SetState(State::WALK);
		knight->SetHealth(knight->GetKnightHealth());
		knight->SetDamage(knight->GetKnightDamage());
		//knight

		//archer
		archer = new Archer();
		archer->Initialize("archer.txt");
		//archer->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		archer->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		archer->material.texture.LoadFromPath(PATH::archer_move);
		archer->animation.Initialize(8, shader);

		archer->SetState(State::WALK);
		archer->SetHealth(archer->GetArcherHealth());
		archer->SetDamage(archer->GetArcherDamage());
		archer->SetAttackRange(archer->GetArcherAttackRange());
		//archer

		//magician
		magician = new Magician();
		magician->Initialize("wizard.txt");
		//magician->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		magician->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		magician->material.texture.LoadFromPath(PATH::wizard_move);
		magician->animation.Initialize(8, shader);

		magician->SetState(State::WALK);
		magician->SetHealth(magician->GetMagicianHealth());
		magician->SetDamage(magician->GetMagicianDamage());
		magician->SetAttackRange(magician->GetMagicianAttackRange());
		//magician

		//sword attack
		swordAttack = new Object();
		swordAttack->Initialize("swordAttack.txt");
		//swordAttack->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		swordAttack->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);

		swordAttack->SetDamage(knight->GetKnightDamage());
		//sword attack

		//fireball
		fireball = new Object();
		fireball->Initialize("fireball.txt");
		//fireball->material.mesh = MESH::create_rectangle(0.0f, 0.0f, 1.0f, 1.0f, color);
		fireball->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		fireball->material.texture.LoadFromPath(PATH::fireball);
		fireball->animation.Initialize(3, shader);

		fireball->SetState(State::WALK);
		fireball->SetDamage(magician->GetMagicianDamage());
		//fireball

		//arrow
		arrow.Initialize("arrow.txt");
		//arrow.material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		arrow.material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		arrow.material.texture.LoadFromPath(PATH::arrow);
		arrow.animation.Initialize(1, shader);

		arrow.SetState(State::WALK);
		arrow.SetDamage(archer->GetArcherDamage());
		//arrow
	}
	
	//test sound and make object
	SOUNDMANAGER->Initialize();
	SOUNDMANAGER->LoadFile("sound.mp3");
	SOUNDMANAGER->LoadFile("beep.wav");
	SOUNDMANAGER->LoadFile("hit.ogg");
	SOUNDMANAGER->PlaySound(1, 0);
	SOUNDMANAGER->SetSystemSoundVolume(0.5f);
	//test sound and make object
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
	Draw::StartDrawing();

	Draw::draw(backgroundShader, { backgroundVertices, backgroundTexture });
	const mat3<float> backgroundNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * background.transform.GetModelToWorld();
	backgroundShader.SendUniformVariable("ndc", backgroundNDC);
	
	Draw::DrawText(fontShader, text);
	const mat3<float> textNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * textTransform.GetModelToWorld();
	fontShader.SendUniformVariable("ndc", textNDC);

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
			Draw::draw(shader, obj.second->material);
		}
	}
	//dynamic test

	Draw::FinishDrawing();
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
	window.SwapBuffers();
	window.PollEvents();
	deltaTime = clock.GetTimeFromLastUpdate();
}

void Application::ShutDown()
{
	isRunning = false;
	if ((bool)glfwWindowShouldClose(window.window) != true)
	{
		glfwSetWindowShouldClose(window.window, GLFW_FALSE);
	}
}

void Application::HandleKeyPress(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::Escape:
		this->ShutDown();
		break;
	case KeyboardButton::F:
		window.ToggleFullScreen();
		break;
	case KeyboardButton::V:
		window.ToggleVSync(!window.IsVSyncOn());
		break;
	case KeyboardButton::W:
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
	case KeyboardButton::S:
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
	case KeyboardButton::A:
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
	case KeyboardButton::D:
		//pressDirection.x += 2.0f;
		SOUNDMANAGER->PlaySound(0, 1);
		OBJECTFACTORY->CopyObject(proKevin);
		//object.speed.x = 0.8f;
		break;
	case KeyboardButton::Z:
		//cameraAngle += 0.025f;
		break;
	case KeyboardButton::X:
		//cameraAngle -= 0.025f;
		break;
	default:;
	}
}

void Application::HandleKeyRelease(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::W:
		pressDirection.y = 0;
		//object.speed.y = 0.f;
		break;
	case KeyboardButton::S:
		pressDirection.y = 0;
		//object.speed.y = 0.f;
		break;
	case KeyboardButton::A:
		pressDirection.x = 0;
		//object.speed.x = 0.f;
		break;
	case KeyboardButton::D:
		pressDirection.x = 0;
		//object.speed.x = 0.f;
		break;
	case KeyboardButton::Z:
		cameraAngle = 0.0f;
		break;
	case KeyboardButton::X:
		cameraAngle = 0.0f;
		break;
	default:;
	}
}

void Application::HandleMouseEvent(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT_PRESS:
	{
		//mouse check
		if (object.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
		{
			object.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButton::LEFT_RELEASE:
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
	zoom = std::clamp(zoom, 0.5f, 2.0f);
	background.transform.SetScale({ window.GetWindowWidth() * (1.f / zoom),
		window.GetWindowHeight() * (1.f / zoom) });
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

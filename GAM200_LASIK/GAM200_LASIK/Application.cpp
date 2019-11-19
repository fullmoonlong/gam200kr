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
#include "Application.h"
#include "VerticesDescription.h"
#include "Image.hpp"
#include "ComponentTest.h"

Application::Application()
{
	Initialize();
	isRunning = true;
	check = MovestateType::MOVE;
}

void Application::Initialize()
{
	window.CanCreateWindow(800, 600, this,"Lasik"); 

	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);
	
	const Color4f color{ 0.8f, 0.8f, 0.0f, 1.0f };
	const Color4f color2{ 0.5f, 0.5f, 0.3f, 1.0f };

	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextCoordinate };
	
	//camera
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);
	//camera

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
	//SOUNDMANAGER->PlaySound(1, 0);
	//test sound and make object

}

void Application::Update()
{
	clock.UpdateClock();

	OBJECTFACTORY->Update();

	//Draw
	draw.StartDrawing();

	//dynamic test
	/*vec2<float> a = {(window.GetWindowWidth()/2.f) , (window.GetWindowHeight()/2.f)};
	transform.SetTranslation(a);
	const mat3<float> ndc1 = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
	shader.SendUniformVariable("ndc", ndc1);
	draw.draw(shader, material);*/

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

	
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(window.GetWindowWidth(), window.GetWindowHeight());
	view.SetZoom(zoom);


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
	
	OBJECTFACTORY->DamageTest(time); //test for damage
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
		SOUNDMANAGER->PlaySound(0, 1);
		OBJECTFACTORY->CopyObject(knight);
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
		OBJECTFACTORY->CopyObject(archer);
		/*OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1)->AddComponent<TestComponent>();
		OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1)->GetComponent<TestComponent>()->object = OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1);
		OBJECTFACTORY->FindObjectwithID(OBJECTFACTORY->GetLastObjectID() - 1)->GetComponent<TestComponent>()->attack = fireball;*/
		break;
	case KeyboardButtons::X:
		//cameraAngle -= 0.025f;
		OBJECTFACTORY->CopyObject(magician);
		break;
	default:;
	}
}

void Application::HandleKeyRelease(KeyboardButtons button)
{
	switch (button)
	{
	/*case KeyboardButtons::W:
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
		if (Knight.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
		{
			Knight.isMouseCollide = true;
		}
		//mouse check
		if (Skeleton.isCollideWithMouse(mousePosition, window.GetWindowWidth(), window.GetWindowHeight()))
		{
			Skeleton.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButtons::LEFT_RELEASE:
		Knight.isMouseCollide = false;
		Skeleton.isMouseCollide = false;
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
	vec2<float> newMousePosition{ xpos, ypos };
	mousePosition = { xpos, ypos };
}

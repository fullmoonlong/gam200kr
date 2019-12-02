/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Jookyung Lee jookyung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "PATH.hpp"
#include "VerticesDescription.h"
#include "Image.hpp"
#include "ComponentTower.h"
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
	backgroundVertices.InitializeWithMeshAndLayout(rectangle, layout);
	backgroundTexture.LoadFromPath(PATH::background);
	background.transform.SetScale({ 1000 });
	//background
	
	// unit initialize
	{
		//tower
		tower = new Object();
		tower->SetState(State::IDLE);
		tower->SetHealth(300);
		tower->SetDamage(0);
		tower->Initialize("tower.txt");
		//proKevin->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		tower->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		tower->material.texture.LoadFromPath(PATH::tower);
		tower->animation.Initialize(1, shader);


		OBJECTFACTORY->CopyObject(tower);
		//tower

		//lair
		lair = new Object();
		lair->SetState(State::IDLE);
		lair->SetHealth(300);
		lair->SetDamage(0);
		lair->Initialize("lair.txt");
		//proKevin->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		lair->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lair->material.texture.LoadFromPath(PATH::tower);
		lair->animation.Initialize(1, shader);

		lair->AddComponent<LairComponent>();
		OBJECTFACTORY->CopyObject(lair);
		//lair

		//kevin
		proKevin = new Object();
		proKevin->SetState(State::WALK);
		proKevin->SetHealth(100);
		proKevin->SetDamage(15);
		proKevin->SetAttackRange({ 1.0f, 0.0f });
		proKevin->Initialize("enemyPrototype.txt");
		//proKevin->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		proKevin->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		proKevin->material.texture.LoadFromPath(PATH::kevin_move);
		proKevin->animation.Initialize(8, shader);

		//kevin

		//knight
		knight = new Knight();
		knight->SetState(State::WALK);
		knight->SetHealth(knight->GetKnightHealth());
		knight->SetDamage(knight->GetKnightDamage());
		knight->Initialize("knight.txt");;
		//knight->material.mesh = MESH::create_rectangle(0.0f, 0.0f, 1.0f, 1.0f, color);
		knight->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		knight->material.texture.LoadFromPath(PATH::knight_move);
		knight->animation.Initialize(8, shader);

		//knight

		//archer
		archer = new Archer();
		archer->Initialize("archer.txt");
		archer->SetState(State::WALK);
		archer->SetHealth(archer->GetArcherHealth());
		archer->SetDamage(archer->GetArcherDamage());
		archer->SetAttackRange(archer->GetArcherAttackRange());
		//archer->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		archer->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		archer->material.texture.LoadFromPath(PATH::archer_move);
		archer->animation.Initialize(8, shader);

		//archer

		//magician
		magician = new Magician();
		magician->SetState(State::WALK);
		magician->SetHealth(magician->GetMagicianHealth());
		magician->SetDamage(magician->GetMagicianDamage());
		magician->SetAttackRange(magician->GetMagicianAttackRange());
		magician->Initialize("wizard.txt");
		//magician->material.mesh = MESH::create_rectangle(0.f, 0.f, 1.0f, 1.0f, color);
		magician->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		magician->material.texture.LoadFromPath(PATH::magician_move);
		magician->animation.Initialize(8, shader);

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

			const mat3<float> ndcHP = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->healthBar.transform.GetModelToWorld();
			shader.SendUniformVariable("ndc", ndcHP);
			Draw::draw(shader, obj.second->healthBar.material);
		
			if (obj.second->GetName() == "Lair")
			{
				obj.second->GetComponent<LairComponent>()->SpawnEnemy(proKevin, clock.timePassed);
			}
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
		//std::cout << time << std::endl;
		//std::cout << frameCount << std::endl;
		clock.timePassed -= 1.0f;
		frameCount = 0;

		//some functions about delay
		OBJECTFACTORY->DamageTest(time); //test for damage
		//some functions about delay
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

void Application::HandleKeyPress(KeyboardButtons button)
{
	static bool isEnter = false;
	switch (button)
	{
	case KeyboardButtons::A:
		if (isEnter == true)
		{
			input.TakeAsInput('a');
			printf("a");
			break;
		}
		break;
	case KeyboardButtons::B:
		if (isEnter == true)
		{
			input.TakeAsInput('b');
			printf("b");
			break;
		}
		break;
	case KeyboardButtons::C:
		if (isEnter == true)
		{
			input.TakeAsInput('c');
			printf("c");
			break;
		}
		break;
	case KeyboardButtons::D:
		if (isEnter == true)
		{
			input.TakeAsInput('d');
			printf("d");
			break;
		}
		break;
	case KeyboardButtons::E:
		if (isEnter == true)
		{
			input.TakeAsInput('e');
			printf("e");
			break;
		}
		break;
	case KeyboardButtons::F:
		if (isEnter == true)
		{
			input.TakeAsInput('f');
			printf("f");
			break;
		}
		else
		{
			window.ToggleFullScreen();
		}
		break;
	case KeyboardButtons::G:
		if (isEnter == true)
		{
			input.TakeAsInput('g');
			printf("g");
			break;
		}
		break;
	case KeyboardButtons::H:
		if (isEnter == true)
		{
			input.TakeAsInput('h');
			printf("h");
			break;
		}
		break;
	case KeyboardButtons::I:
		if (isEnter == true)
		{
			input.TakeAsInput('i');
			printf("i");
			break;
		}
		break;
	case KeyboardButtons::J:
		if (isEnter == true)
		{
			input.TakeAsInput('j');
			printf("j");
			break;
		}
		break;
	case KeyboardButtons::K:
		if (isEnter == true)
		{
			input.TakeAsInput('k');
			printf("k");
			break;
		}
		break;
	case KeyboardButtons::L:
		if (isEnter == true)
		{
			input.TakeAsInput('l');
			printf("l");
			break;
		}
		break;
	case KeyboardButtons::M:
		if (isEnter == true)
		{
			input.TakeAsInput('m');
			printf("m");
			break;
		}
		break;
	case KeyboardButtons::N:
		if (isEnter == true)
		{
			input.TakeAsInput('n');
			printf("n");
			break;
		}
		break;
	case KeyboardButtons::O:
		if (isEnter == true)
		{
			input.TakeAsInput('o');
			printf("o");
			break;
		}
		break;
	case KeyboardButtons::P:
		if (isEnter == true)
		{
			input.TakeAsInput('p');
			printf("p");
			break;
		}
		break;
	case KeyboardButtons::Q:
		if (isEnter == true)
		{
			input.TakeAsInput('q');
			printf("q");
			break;
		}
		break;
	case KeyboardButtons::R:
		if (isEnter == true)
		{
			input.TakeAsInput('r');
			printf("r");
			break;
		}
		break;
	case KeyboardButtons::S:
		if (isEnter == true)
		{
			input.TakeAsInput('s');
			printf("s");
			break;
		}
		else
		{
			for (auto obj : OBJECTFACTORY->GetObjecteList())
			{
				if (obj.second->GetType() == UnitType::Player)
				{
					OBJECTFACTORY->Destroy(obj.second);
				}
			}
		}
		break;
	case KeyboardButtons::T:
		if (isEnter == true)
		{
			input.TakeAsInput('t');
			printf("t");
			break;
		}
		break;
	case KeyboardButtons::U:
		if (isEnter == true)
		{
			input.TakeAsInput('u');
			printf("u");
			break;
		}
		break;
	case KeyboardButtons::V:
		if (isEnter == true)
		{
			input.TakeAsInput('v');
			printf("v");
			break;
		}
		else
		{
			if (window.IsVSyncOn() == false)
			{
				window.ToggleVSync(true);
				break;
			}
			window.ToggleVSync(false);
		}
		break;
	case KeyboardButtons::W:
		if (isEnter == true)
		{
			input.TakeAsInput('w');
			printf("w");
			break;
		}
		break;
	case KeyboardButtons::X:
		if (isEnter == true)
		{
			input.TakeAsInput('x');
			printf("x");
			break;
		}
		break;
	case KeyboardButtons::Y:
		if (isEnter == true)
		{
			input.TakeAsInput('y');
			printf("y");
			break;
		}
		break;
	case KeyboardButtons::Z:
		if (isEnter == true)
		{
			input.TakeAsInput('z');
			printf("z");
			break;
		}
		break;
	case KeyboardButtons::Escape:
		this->ShutDown();
		break;
	case KeyboardButtons::Enter:
		if (isEnter == false)
		{
			isEnter = true;
			printf("typing start\n");
			break;
		}
		isEnter = false;
		printf("typing end\n");
		std::cout << "\n" << input.GetString();
		if (input.MatchStringWithInput() == 1)
		{
			OBJECTFACTORY->CopyObject(knight);
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
		}
		input.SetString("");
		break;

	default:
		break;
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

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
	const VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	const Mesh& rectangle = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);

	bitmapFont.LoadFromFile(PATH::bitmapfont_fnt);
	text.SetFont(bitmapFont);

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
		proKevin->material.shader = shader;
		proKevin->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		proKevin->material.texture.LoadFromPath(PATH::kevin_move);
		proKevin->animation.Initialize({ 8, 10.0f }, shader);

		proKevin->SetState(State::WALK);
		proKevin->SetHealth(100);
		proKevin->SetDamage(15);
		proKevin->SetAttackRange({ 1.0f, 0.0f });
		//kevin

		//knight
		knight = new Knight();
		knight->Initialize("knight.txt");
		knight->material.shader = shader;
		knight->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		knight->material.texture.LoadFromPath(PATH::knight_move);
		knight->animation.Initialize({ 8, 10.0f }, shader);

		knight->SetState(State::WALK);
		knight->SetHealth(knight->GetKnightHealth());
		knight->SetDamage(knight->GetKnightDamage());
		//knight

		//archer
		archer = new Archer();
		archer->Initialize("archer.txt");
		archer->material.shader = shader;
		archer->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		archer->material.texture.LoadFromPath(PATH::archer_move);
		archer->animation.Initialize({ 8, 10.0f }, shader);

		archer->SetState(State::WALK);
		archer->SetHealth(archer->GetArcherHealth());
		archer->SetDamage(archer->GetArcherDamage());
		archer->SetAttackRange(archer->GetArcherAttackRange());
		//archer

		//magician
		magician = new Magician();
		magician->Initialize("wizard.txt");
		magician->material.shader = shader;
		magician->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		magician->material.texture.LoadFromPath(PATH::wizard_move);
		magician->animation.Initialize({ 8, 10.0f }, shader);

		magician->SetState(State::WALK);
		magician->SetHealth(magician->GetMagicianHealth());
		magician->SetDamage(magician->GetMagicianDamage());
		magician->SetAttackRange(magician->GetMagicianAttackRange());
		//magician

		//sword attack
		swordAttack = new Object();
		swordAttack->Initialize("swordAttack.txt");
		swordAttack->material.shader = shader;
		swordAttack->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);

		swordAttack->SetDamage(knight->GetKnightDamage());
		//sword attack

		//fireball
		fireball = new Object();
		fireball->Initialize("fireball.txt");
		fireball->material.shader = shader;
		fireball->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		fireball->material.texture.LoadFromPath(PATH::fireball);
		fireball->animation.Initialize({ 3, 5.0f }, shader);

		fireball->SetState(State::WALK);
		fireball->SetDamage(magician->GetMagicianDamage());
		//fireball

		//arrow
		arrow.Initialize("arrow.txt");
		arrow.material.shader = shader;
		arrow.material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		arrow.material.texture.LoadFromPath(PATH::arrow);
		arrow.animation.Initialize({1, 5.0f}, shader);

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
	
	Draw::StartDrawing();

	const mat3<float> backgroundNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * background.transform.GetModelToWorld();
	Draw::draw({ backgroundShader, backgroundVertices, backgroundNDC,  backgroundTexture });
	
	const mat3<float> textNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * textTransform.GetModelToWorld();
	text.SetString(input.GetString());
	Draw::DrawText(fontShader, textNDC, text);
	
	//dynamic test
	for (auto obj : OBJECTFACTORY->GetObjecteList())
	{
		if (obj.second != nullptr)
		{
			obj.second->Update(deltaTime);
			obj.second->ChangeUnitAnimation();
			obj.second->animation.Animate(deltaTime);
			const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->transform.GetModelToWorld();
			obj.second->material.ndc = ndc;
			Draw::draw(obj.second->material);
		}
	}
	//dynamic test

	Draw::FinishDrawing();

	++frameCount;
	static int time = 0;
	if (clock.timePassed >= 1.0f)
	{
		++time;
		clock.timePassed -= 1.0f;
		frameCount = 0;
		OBJECTFACTORY->DamageTest(time);	//test for damage
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
	static bool isEnter = false;
	switch (button)
	{
	case KeyboardButton::A:
		if (isEnter == true)
		{
			input.TakeAsInput('a');
			printf("a");
			break;
		}
		break;
	case KeyboardButton::B:
		if (isEnter == true)
		{
			input.TakeAsInput('b');
			printf("b");
			break;
		}
		break;
	case KeyboardButton::C:
		if (isEnter == true)
		{
			input.TakeAsInput('c');
			printf("c");
			break;
		}
		break;
	case KeyboardButton::D:
		if (isEnter == true)
		{
			input.TakeAsInput('d');
			printf("d");
			break;
		}
		break;
	case KeyboardButton::E:
		if (isEnter == true)
		{
			input.TakeAsInput('e');
			printf("e");
			break;
		}
		break;
	case KeyboardButton::F:
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
	case KeyboardButton::G:
		if (isEnter == true)
		{
			input.TakeAsInput('g');
			printf("g");
			break;
		}
		break;
	case KeyboardButton::H:
		if (isEnter == true)
		{
			input.TakeAsInput('h');
			printf("h");
			break;
		}
		break;
	case KeyboardButton::I:
		if (isEnter == true)
		{
			input.TakeAsInput('i');
			printf("i");
			break;
		}
		break;
	case KeyboardButton::J:
		if (isEnter == true)
		{
			input.TakeAsInput('j');
			printf("j");
			break;
		}
		break;
	case KeyboardButton::K:
		if (isEnter == true)
		{
			input.TakeAsInput('k');
			printf("k");
			break;
		}
		break;
	case KeyboardButton::L:
		if (isEnter == true)
		{
			input.TakeAsInput('l');
			printf("l");
			break;
		}
		break;
	case KeyboardButton::M:
		if (isEnter == true)
		{
			input.TakeAsInput('m');
			printf("m");
			break;
		}
		break;
	case KeyboardButton::N:
		if (isEnter == true)
		{
			input.TakeAsInput('n');
			printf("n");
			break;
		}
		break;
	case KeyboardButton::O:
		if (isEnter == true)
		{
			input.TakeAsInput('o');
			printf("o");
			break;
		}
		break;
	case KeyboardButton::P:
		if (isEnter == true)
		{
			input.TakeAsInput('p');
			printf("p");
			break;
		}
		break;
	case KeyboardButton::Q:
		if (isEnter == true)
		{
			input.TakeAsInput('q');
			printf("q");
			break;
		}
		break;
	case KeyboardButton::R:
		if (isEnter == true)
		{
			input.TakeAsInput('r');
			printf("r");
			break;
		}
		break;
	case KeyboardButton::S:
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
	case KeyboardButton::T:
		if (isEnter == true)
		{
			input.TakeAsInput('t');
			printf("t");
			break;
		}
		break;
	case KeyboardButton::U:
		if (isEnter == true)
		{
			input.TakeAsInput('u');
			printf("u");
			break;
		}
		break;
	case KeyboardButton::V:
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
	case KeyboardButton::W:
		if (isEnter == true)
		{
			input.TakeAsInput('w');
			printf("w");
			break;
		}
		break;
	case KeyboardButton::X:
		if (isEnter == true)
		{
			input.TakeAsInput('x');
			printf("x");
			break;
		}
		break;
	case KeyboardButton::Y:
		if (isEnter == true)
		{
			input.TakeAsInput('y');
			printf("y");
			break;
		}
		break;
	case KeyboardButton::Z:
		if (isEnter == true)
		{
			input.TakeAsInput('z');
			printf("z");
			break;
		}
		break;
	case KeyboardButton::Escape:
		this->ShutDown();
		break;
	case KeyboardButton::Enter:
		if (isEnter == false)
		{
			isEnter = true;
			printf("typing start\n");
			break;
		}
		isEnter = false;
		printf("typing end\n");
		//std::cout << "\n" << input.GetString();
		if (input.MatchStringWithInput() == 1)
		{
			OBJECTFACTORY->CopyObject(knight);
		}
		else if (input.MatchStringWithInput() == 2)
		{
			OBJECTFACTORY->CopyObject(archer);
		}
		else if (input.MatchStringWithInput() == 3)
		{
			OBJECTFACTORY->CopyObject(magician);
		}
		input.SetString(L"");
		break;

	default:
		break;
	}
}

void Application::HandleKeyRelease(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::W:
		pressDirection.y = 0;
		break;
	case KeyboardButton::S:
		pressDirection.y = 0;
		break;
	case KeyboardButton::A:
		pressDirection.x = 0;
		break;
	case KeyboardButton::D:
		pressDirection.x = 0;
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
	mousePosition = { xpos, ypos };
}

void Application::HandleWindowClose()
{
	ShutDown();
}

#include "LevelTest1.h"
#include <iostream>

#include "Application.h"
#include "ObjectFactory.h"
#include "VerticesDescription.h"
#include "Image.hpp"
#include "ComponentTest.h"
#include "ComponentTower.h"
#include "ObjectMaterial.h"

LevelTest1::LevelTest1(OpenGLWindow* window)
{
	windowPoint = window;
	std::cout << "Add LevelTest1 Sucessful" << std::endl;
}

LevelTest1::~LevelTest1()
{
	std::cout << "Close LevelTest1 Sucessful" << std::endl;
}

void LevelTest1::Initialize()
{
	std::cout << "Load LevelTest1 Sucessful" << std::endl;

	shader.LoadShaderFrom(PATH::animation_vert, PATH::animation_frag);	//shaders for animation
	fontShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);

	const Color4f color{ 1.0f, 1.0f, 1.0f, 1.0f };
	const VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	const Mesh& rectangle = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);

	bitmapFont.LoadFromFile(PATH::bitmapfont_fnt);
	text.SetFont(bitmapFont);

	textTransform.SetTranslation({ -300.0f, 0.0f });

	//camera
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);
	//camera

	//background
	backgroundShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	backgroundMesh.SetShapePattern(ShapePattern::TriangleFan);
	backgroundVertices.InitializeWithMeshAndLayout(rectangle, layout);
	backgroundTexture.LoadFromPath(PATH::background);
	background.transform.SetScale({ 1280, 720 });
	//background

	// unit initialize
	{
		//tower
		tower = new Object();
		tower->SetState(State::IDLE);
		tower->SetHealth(300);
		tower->SetDamage(0);
		tower->Initialize("tower.txt");
		tower->material.shader = fontShader;
		tower->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		tower->material.texture.LoadFromPath(PATH::tower);


		OBJECTFACTORY->CopyObject(tower);
		//tower

		//lair
		lair = new Object();
		lair->SetState(State::IDLE);
		lair->SetHealth(300);
		lair->SetDamage(0);
		lair->Initialize("lair.txt");
		lair->material.shader = fontShader;
		lair->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lair->material.texture.LoadFromPath(PATH::lair);

		lair->AddComponent<LairComponent>();
		OBJECTFACTORY->CopyObject(lair);
		//lair

		skeleton = new Skeleton();
		skeleton->SetState(State::WALK);
		skeleton->SetHealth(skeleton->GetSkeletionHealth());
		skeleton->SetDamage(skeleton->GetSkeletionDamage());
		skeleton->SetAttackRange({ 1.0f, 0.0f });
		skeleton->Initialize("skeleton.txt");
		skeleton->material.shader = shader;
		skeleton->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		skeleton->material.texture.LoadFromPath(PATH::skeleton_move);
		skeleton->animation.Initialize({ 4, 1,	10.0f }, shader);

		golem = new Golem();
		golem->SetState(State::WALK);
		golem->SetHealth(golem->GetGolemHealth());
		golem->SetDamage(golem->GetGolemHealth());
		golem->SetAttackRange({ 1.0f, 0.0f });
		golem->Initialize("golem.txt");
		golem->material.shader = shader;
		golem->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		golem->material.texture.LoadFromPath(PATH::golem_move);
		golem->animation.Initialize({ 4, 1,	10.0f }, shader);

		lich = new Lich();
		lich->SetState(State::WALK);
		lich->SetHealth(lich->GetLichHealth());
		lich->SetDamage(lich->GetLichDamage());
		lich->SetAttackRange(lich->GetLichAttackRange());
		lich->Initialize("lich.txt");
		lich->material.shader = shader;
		lich->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lich->material.texture.LoadFromPath(PATH::lich_move);
		lich->animation.Initialize({ 8, 1, 10.0f }, shader);

		//knight
		knight = new Knight();
		knight->SetState(State::WALK);
		knight->SetHealth(knight->GetKnightHealth());
		knight->SetDamage(knight->GetKnightDamage());
		knight->Initialize("knight.txt");
		knight->material.shader = shader;
		knight->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		knight->material.texture.LoadFromPath(PATH::knight_move);
		knight->animation.Initialize({ 8, 1, 10.0f }, shader);

		//knight

		//archer
		archer = new Archer();
		archer->SetState(State::WALK);
		archer->SetHealth(archer->GetArcherHealth());
		archer->SetDamage(archer->GetArcherDamage());
		archer->SetAttackRange(archer->GetArcherAttackRange());
		archer->Initialize("archer.txt");
		archer->material.shader = shader;
		archer->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		archer->material.texture.LoadFromPath(PATH::archer_move);
		archer->animation.Initialize({ 8, 1, 10.0f }, shader);

		//archer

		//magician
		magician = new Magician();
		magician->SetState(State::WALK);
		magician->SetHealth(magician->GetMagicianHealth());
		magician->SetDamage(magician->GetMagicianDamage());
		magician->SetAttackRange(magician->GetMagicianAttackRange());
		magician->Initialize("wizard.txt");
		magician->material.shader = shader;
		magician->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		magician->material.texture.LoadFromPath(PATH::magician_move);
		magician->animation.Initialize({ 8, 1, 10.0f }, shader);

		//magician

		//sword attack
		swordAttack = new Object();
		swordAttack->SetHealth(0);
		swordAttack->Initialize("swordAttack.txt");
		swordAttack->SetState(State::WALK);
		swordAttack->material.shader = shader;
		swordAttack->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		swordAttack->SetDamage(knight->GetKnightDamage());

		knight->GetComponent<TestComponent>()->attack = swordAttack;
		//sword attack

		//sword attack
		enemyAttack = new Object();
		enemyAttack->SetHealth(0);
		enemyAttack->Initialize("enemyAttack.txt");
		enemyAttack->SetState(State::WALK);
		enemyAttack->material.shader = shader;
		enemyAttack->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		
		enemyAttack->SetDamage(skeleton->GetSkeletionDamage());
		skeleton->GetComponent<TestComponent>()->attack = enemyAttack;
		
		enemyAttack->SetDamage(golem->GetGolemDamage());
		golem->GetComponent<TestComponent>()->attack = enemyAttack;
		//sword attack


		//fireball
		fireball = new Object();
		fireball->Initialize("fireball.txt");
		fireball->material.shader = shader;
		fireball->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		fireball->material.texture.LoadFromPath(PATH::fireball);
		fireball->animation.Initialize({ 3, 1, 5.0f }, shader);

		fireball->SetState(State::WALK);
		fireball->SetDamage(magician->GetMagicianDamage());

		magician->GetComponent<TestComponent>()->attack = fireball;
		//fireball

		//fireball
		fireballEnemy = new Object();
		fireballEnemy->Initialize("fireballEnemy.txt");
		fireballEnemy->material.shader = shader;
		fireballEnemy->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		fireballEnemy->material.texture.LoadFromPath(PATH::fireball);
		fireballEnemy->animation.Initialize({ 3, 1, 5.0f }, shader);

		fireballEnemy->SetState(State::WALK);
		fireballEnemy->SetDamage(lich->GetLichDamage());

		lich->GetComponent<TestComponent>()->attack = fireballEnemy;
		//fireball

		//arrow
		arrow.Initialize("arrow.txt");
		arrow.material.shader = fontShader;
		arrow.material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		arrow.material.texture.LoadFromPath(PATH::arrow);

		arrow.SetState(State::WALK);
		arrow.SetDamage(archer->GetArcherDamage());

		archer->GetComponent<TestComponent>()->attack = &arrow;
		//arrow
	}

	//test sound and make object
	SOUNDMANAGER->Initialize();
	SOUNDMANAGER->LoadFile("sound.mp3");
	SOUNDMANAGER->LoadFile("beep.wav");
	SOUNDMANAGER->LoadFile("hit.ogg");
	//SOUNDMANAGER->PlaySound(1, 0);
	SOUNDMANAGER->SetSystemSoundVolume(0.5f);
	//test sound and make object
	selectMenu.SelectMenu();
	coolTime.Initialize(camera, view);
	windowPoint->SwapBuffers();
}

void LevelTest1::Update(float dt)
{
	OBJECTFACTORY->Update();
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);
	//Transform

	//Draw
	Draw::StartDrawing();

	const mat3<float> backgroundNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * background.transform.GetModelToWorld();
	Draw::draw({ backgroundShader, backgroundVertices, backgroundNDC,  backgroundTexture });

	const mat3<float> textNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * textTransform.GetModelToWorld();
	text.SetString(input.GetString());
	Draw::DrawText(fontShader, textNDC, text);

	coolTime.CoolDownUpdate(dt);

	//dynamic test
	for (auto obj : OBJECTFACTORY->GetObjecteList())
	{
		if (obj.second != nullptr)
		{

			obj.second->animation.Animate(dt);
			obj.second->Update(dt);
			obj.second->ChangeUnitAnimation();

			const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->transform.GetModelToWorld();
			obj.second->GetComponent<MaterialComponent>()->material.ndc = ndc;
			Draw::draw(obj.second->GetComponent<MaterialComponent>()->material);

			//hpbar
			if (obj.second->GetType() == UnitType::Player || obj.second->GetType() == UnitType::Enemy)
			{
				obj.second->healthBar.material.shader = fontShader; //texture shader
				const mat3<float> ndcHP = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->healthBar.transform.GetModelToWorld();
				obj.second->healthBar.material.ndc = ndcHP;
				Draw::draw(obj.second->healthBar.material);
			}
			//hpbar

			if (obj.second->GetName() == "Lair")
			{
				obj.second->GetComponent<LairComponent>()->SpawnEnemy(skeleton, dt);
			}
		}
	}
	//dynamic test
	selectMenu.SelectUpdate(camera, view);
	Draw::FinishDrawing();
}

void LevelTest1::Shutdown()
{
	OBJECTFACTORY->DestroyAllObjects();
}

void LevelTest1::HandleKeyPress(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::A:
		if (isEnter == true)
		{
			input.TakeAsInput('a');
			printf("a");
			break;
		}
		else
		{
			OBJECTFACTORY->CopyObject(lich);
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
		else
		{
			OBJECTFACTORY->CopyObject(skeleton);
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
				if (obj.second->GetName() != "Tower")
				{
					if (obj.second->GetType() == UnitType::Player)
					{
						OBJECTFACTORY->Destroy(obj.second);
					}
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
		break;
	case KeyboardButton::W:
		if (isEnter == true)
		{
			input.TakeAsInput('w');
			printf("w");
			break;
		}
		else
		{
			for (auto obj : OBJECTFACTORY->GetObjecteList())
			{
				if (obj.second->GetName() != "Lair")
				{
					if (obj.second->GetType() == UnitType::Enemy)
					{
						OBJECTFACTORY->Destroy(obj.second);
					}
				}
			}
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
			coolTime.SetKnightCoolDown();
		}
		else if (input.MatchStringWithInput() == 2)
		{
			OBJECTFACTORY->CopyObject(archer);
			coolTime.SetArcherCoolDown();
		}
		else if (input.MatchStringWithInput() == 3)
		{
			OBJECTFACTORY->CopyObject(magician);
			coolTime.SetMagicianCoolDown();
		}
		input.SetString(L"");
		break;

	default:
		break;
	}
}

void LevelTest1::HandleKeyRelease(KeyboardButton button)
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

void LevelTest1::HandleMouseEvent(MouseButton button)
{
	switch (button)
	{
	case MouseButton::LEFT_PRESS:
	{
		//mouse check
		if (object.isCollideWithMouse(mousePosition, windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight()))
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

void LevelTest1::HandleResizeEvent(const int& new_width, const int& new_height)
{
	view.SetViewSize(new_width, new_height);
	view.SetZoom(zoom);
}

void LevelTest1::HandleScrollEvent(float /*scroll_amount*/)
{
	//zoom = view.GetZoom() + (scroll_amount * 0.05f);
	zoom = std::clamp(zoom, 0.5f, 2.0f);
	background.transform.SetScale({ windowPoint->GetWindowWidth() * (1.f / zoom),
		windowPoint->GetWindowHeight() * (1.f / zoom) });
	view.SetZoom(zoom);
}

void LevelTest1::HandleMousePositionEvent(float xpos, float ypos)
{
	mousePosition = { xpos, ypos };
}
//
//void LevelTest1::HandleWindowClose()
//{
//}

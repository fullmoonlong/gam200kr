/**************************************************************************************
 *	File Name        : LevelTest1.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Jookyung Lee
 *	Secondary Author : Wonju Cho
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include <iostream>
#include "Image.hpp"
#include "LevelTest1.h"
#include "GameManager.h"
#include "Application.h"
#include "ObjectFactory.h"
#include "ComponentTest.h"
#include "ComponentTower.h"
#include "ObjectMaterial.h"
#include "VerticesDescription.h"
#include "UnitStateComponent.hpp"


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
	isPlayerWin = false;
	isEnemyWin = false;
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

	//win
	winpic = new Object();
	winpic->transform.SetTranslation({ 0.f, 0.f });
	winpic->transform.SetScale({ 640, 360 });
	winpic->material.shader = fontShader;
	winpic->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
	winpic->material.texture.LoadTextureFrom(PATH::winpic);
	winpic->material.ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * winpic->transform.GetModelToWorld();

	//lose
	losepic = new Object();
	losepic->transform.SetTranslation({ 0.f, 0.f });
	losepic->transform.SetScale({ 640, 360 });
	losepic->material.shader = fontShader;
	losepic->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
	losepic->material.texture.LoadTextureFrom(PATH::losepic);
	losepic->material.ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * losepic->transform.GetModelToWorld();

	//background
	backgroundShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	backgroundMesh.SetShapePattern(ShapePattern::TriangleFan);
	backgroundVertices.InitializeWithMeshAndLayout(rectangle, layout);
	backgroundTexture.LoadTextureFrom(PATH::background);
	backgroundMaterial.CreateSprite(backgroundShader, backgroundTexture, backgroundNDC);
	background.transform.SetScale({ 1280, 720 });
	//background

	// unit initialize
	{
		//tower
		tower = new Object();
		tower->AddComponent<BaseUnitState>();
		tower->GetComponent<BaseUnitState>()->SetState(State::IDLE);
		tower->GetComponent<BaseUnitState>()->SetHealth(300);
		tower->GetComponent<BaseUnitState>()->SetDamage(0);
		tower->Initialize("tower.txt");
		tower->material.shader = shader;
		tower->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		tower->material.texture.LoadTextureFrom(PATH::tower);
		tower->animation.Initialize({ 1,1, 1.f }, tower->material.shader);
		GAMEMANAGER->SpawnUnit(tower);
		//tower

		//lair
		lair = new Object();
		lair->AddComponent<BaseUnitState>();
		lair->GetComponent<BaseUnitState>()->SetState(State::IDLE);
		lair->GetComponent<BaseUnitState>()->SetHealth(300);
		lair->GetComponent<BaseUnitState>()->SetDamage(0);
		lair->Initialize("lair.txt");
		lair->material.shader = shader;
		lair->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lair->material.texture.LoadTextureFrom(PATH::lair);
		lair->animation.Initialize({ 1,1, 1.f }, lair->material.shader);
		lair->AddComponent<LairComponent>();
		lair->animation.Initialize({ 1, 1,	10.0f }, shader);
		GAMEMANAGER->SpawnUnit(lair);
		//lair

		skeleton = new Skeleton();
		skeleton->AddComponent<BaseUnitState>();
		skeleton->GetComponent<BaseUnitState>()->SetState(State::WALK);
		skeleton->GetComponent<BaseUnitState>()->SetHealth(skeleton->GetSkeletionHealth());
		skeleton->GetComponent<BaseUnitState>()->SetDamage(skeleton->GetSkeletionDamage());
		skeleton->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });
		skeleton->Initialize("skeleton.txt");
		skeleton->material.shader = shader;
		skeleton->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		skeleton->material.texture.LoadTextureFrom(PATH::skeleton_move);
		skeleton->animation.Initialize({ 4, 1,	10.0f }, shader);

		golem = new Golem();
		golem->AddComponent<BaseUnitState>();
		golem->GetComponent<BaseUnitState>()->SetState(State::WALK);
		golem->GetComponent<BaseUnitState>()->SetHealth(golem->GetGolemHealth());
		golem->GetComponent<BaseUnitState>()->SetDamage(golem->GetGolemHealth());
		golem->GetComponent<BaseUnitState>()->SetAttackRange({ 1.0f, 0.0f });
		golem->Initialize("golem.txt");
		golem->material.shader = shader;
		golem->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		golem->material.texture.LoadTextureFrom(PATH::golem_move);
		golem->animation.Initialize({ 4, 1,	10.0f }, shader);

		lich = new Lich();
		lich->AddComponent<BaseUnitState>();
		lich->GetComponent<BaseUnitState>()->SetState(State::WALK);
		lich->GetComponent<BaseUnitState>()->SetHealth(lich->GetLichHealth());
		lich->GetComponent<BaseUnitState>()->SetDamage(lich->GetLichDamage());
		lich->GetComponent<BaseUnitState>()->SetAttackRange(lich->GetLichAttackRange());
		lich->Initialize("lich.txt");
		lich->material.shader = shader;
		lich->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lich->material.texture.LoadTextureFrom(PATH::lich_move);
		lich->animation.Initialize({ 8, 1, 10.0f }, shader);

		//knight
		knight = new Knight();
		knight->AddComponent<BaseUnitState>();
		knight->GetComponent<BaseUnitState>()->SetState(State::WALK);
		knight->GetComponent<BaseUnitState>()->SetHealth(knight->GetKnightHealth());
		knight->GetComponent<BaseUnitState>()->SetDamage(knight->GetKnightDamage());
		knight->Initialize("knight.txt");
		knight->material.shader = shader;
		knight->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		knight->material.texture.LoadTextureFrom(PATH::knight_move);
		knight->animation.Initialize({ 8, 1, 10.0f }, shader);
		//knight

		//archer
		archer = new Archer();
		archer->AddComponent<BaseUnitState>();
		archer->GetComponent<BaseUnitState>()->SetState(State::WALK);
		archer->GetComponent<BaseUnitState>()->SetHealth(archer->GetArcherHealth());
		archer->GetComponent<BaseUnitState>()->SetDamage(archer->GetArcherDamage());
		archer->GetComponent<BaseUnitState>()->SetAttackRange(archer->GetArcherAttackRange());
		archer->Initialize("archer.txt");
		archer->material.shader = shader;
		archer->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		archer->material.texture.LoadTextureFrom(PATH::archer_move);
		archer->animation.Initialize({ 8, 1, 10.0f }, shader);
		//archer

		//magician
		magician = new Magician();
		magician->AddComponent<BaseUnitState>();
		magician->GetComponent<BaseUnitState>()->SetState(State::WALK);
		magician->GetComponent<BaseUnitState>()->SetHealth(magician->GetMagicianHealth());
		magician->GetComponent<BaseUnitState>()->SetDamage(magician->GetMagicianDamage());
		magician->GetComponent<BaseUnitState>()->SetAttackRange(magician->GetMagicianAttackRange());
		magician->Initialize("wizard.txt");
		magician->material.shader = shader;
		magician->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		magician->material.texture.LoadTextureFrom(PATH::magician_move);
		magician->animation.Initialize({ 8, 1, 10.0f }, shader);
		//magician

		//sword attack
		swordAttack = new Object();
		swordAttack->AddComponent<BaseUnitState>();
		swordAttack->GetComponent<BaseUnitState>()->SetHealth(0);
		swordAttack->Initialize("swordAttack.txt");
		swordAttack->GetComponent<BaseUnitState>()->SetState(State::WALK);
		swordAttack->material.shader = shader;
		swordAttack->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		swordAttack->GetComponent<BaseUnitState>()->SetDamage(knight->GetKnightDamage());
		swordAttack->animation.Initialize({ 1,1, 1.f }, swordAttack->material.shader);

		knight->GetComponent<ObjectAttackComponent>()->attack = swordAttack;
		//sword attack

		//sword attack
		enemyAttack = new Object();
		enemyAttack->AddComponent<BaseUnitState>();
		enemyAttack->GetComponent<BaseUnitState>()->SetHealth(0);
		enemyAttack->Initialize("enemyAttack.txt");
		enemyAttack->GetComponent<BaseUnitState>()->SetState(State::WALK);
		enemyAttack->material.shader = shader;
		enemyAttack->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		enemyAttack->animation.Initialize({ 1,1, 1.f }, enemyAttack->material.shader);

		enemyAttack->GetComponent<BaseUnitState>()->SetDamage(skeleton->GetSkeletionDamage());
		skeleton->GetComponent<ObjectAttackComponent>()->attack = enemyAttack;
		//sword attack


		//fireball
		fireball = new Object();
		fireball->AddComponent<BaseUnitState>();
		fireball->Initialize("fireball.txt");
		fireball->material.shader = shader;
		fireball->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		fireball->material.texture.LoadTextureFrom(PATH::fireball);
		fireball->animation.Initialize({ 3, 1, 5.0f }, shader);
		fireball->GetComponent<BaseUnitState>()->SetState(State::WALK);
		fireball->GetComponent<BaseUnitState>()->SetDamage(magician->GetMagicianDamage());

		magician->GetComponent<ObjectAttackComponent>()->attack = fireball;
		//fireball

		//fireball
		fireballEnemy = new Object();
		fireballEnemy->AddComponent<BaseUnitState>();
		fireballEnemy->Initialize("fireballEnemy.txt");
		fireballEnemy->material.shader = shader;
		fireballEnemy->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		fireballEnemy->material.texture.LoadTextureFrom(PATH::fireball);
		fireballEnemy->animation.Initialize({ 3, 1, 5.0f }, shader);
		fireballEnemy->GetComponent<BaseUnitState>()->SetState(State::WALK);
		fireballEnemy->GetComponent<BaseUnitState>()->SetDamage(lich->GetLichDamage());

		lich->GetComponent<ObjectAttackComponent>()->attack = fireballEnemy;
		//fireball

		//arrow
		arrow = new Object();
		arrow->AddComponent<BaseUnitState>();
		arrow->Initialize("arrow.txt");
		arrow->material.shader = fontShader;
		arrow->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		arrow->material.texture.LoadTextureFrom(PATH::arrow);
		arrow->animation.Initialize({ 1,1, 1.f }, arrow->material.shader);

		arrow->GetComponent<BaseUnitState>()->SetState(State::WALK);
		arrow->GetComponent<BaseUnitState>()->SetDamage(archer->GetArcherDamage());

		archer->GetComponent<ObjectAttackComponent>()->attack = arrow;
		//arrow
	}

	//test sound and make object
	SOUNDMANAGER->Initialize();
	SOUNDMANAGER->LoadFile("backgroundmusic.wav");
	SOUNDMANAGER->LoadFile("Fireball.wav");
	SOUNDMANAGER->LoadFile("archershoot.ogg");
	SOUNDMANAGER->LoadFile("hit.ogg");
	//SOUNDMANAGER->PlaySound(1, 0);
	SOUNDMANAGER->SetSystemSoundVolume(0.5f);
	//test sound and make object
	selectMenu.SelectMenu();
	coolTime.Initialize(camera, view);
	windowPoint->SwapBuffers();

	debugTextTransform.SetTranslation({ -80.0f, 160.0f });

	debugText.SetFont(bitmapFont);
	debugText.SetString(L"debug mode");
}

void LevelTest1::Update(float dt)
{
	OBJECTFACTORY->Update(dt);
	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);
	//Transform

	//Draw
	Draw::StartDrawing();

	backgroundNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * background.transform.GetModelToWorld();
	backgroundMaterial.ndc = backgroundNDC;
	Draw::draw(backgroundMaterial);

	const mat3<float> uiNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * ui.transform.GetModelToWorld();
	ui.material.ndc = uiNDC;
	Draw::draw(ui.material);

	const mat3<float> textNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * textTransform.GetModelToWorld();
	text.SetString(input.GetString());
	Draw::DrawText(fontShader, textNDC, text);

	coolTime.CoolDownUpdate(dt);

	//dynamic test
	for (const auto& obj : OBJECTFACTORY->GetObjecteList())
	{
		if (obj.second != nullptr)
		{
			const auto something = obj.second;
			something->animation.Animate(dt);
			something->Update(dt);
			something->ChangeUnitAnimation();

			const mat3<float> ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->transform.GetModelToWorld();
			obj.second->GetComponent<MaterialComponent>()->material.ndc = ndc;
			Draw::draw(obj.second->GetComponent<MaterialComponent>()->material);

			//hpbar
			if (obj.second->GetComponent<UnitState>()->GetType() == UnitType::Player || obj.second->GetComponent<UnitState>()->GetType() == UnitType::Enemy)
			{
				obj.second->GetComponent<UnitState>()->healthBar.material.shader = fontShader; //texture shader
				const mat3<float> ndcHP = view.GetCameraToNDCTransform() * camera.WorldToCamera() * obj.second->GetComponent<UnitState>()->healthBar.transform.GetModelToWorld();
				obj.second->GetComponent<UnitState>()->healthBar.material.ndc = ndcHP;
				Draw::draw(obj.second->GetComponent<UnitState>()->healthBar.material);
			}
			//hpbar

			if (obj.second->GetName() == "Lair")
			{
				obj.second->GetComponent<LairComponent>()->SpawnEnemy(skeleton, dt);
				if (obj.second->GetComponent<UnitState>()->GetHealth() <= 0)
				{
					isPlayerWin = true;
					GAMEMANAGER->isGameEnd = true;
					OBJECTFACTORY->Destroy(obj.second);
				}
			}
			else if (obj.second->GetName() == "Tower")
			{
				if (obj.second->GetComponent<UnitState>()->GetHealth() <= 0)
				{
					isEnemyWin = true;
					GAMEMANAGER->isGameEnd = true;
					OBJECTFACTORY->Destroy(obj.second);
				}
			}
		}
	}
	Win();
	Lose();
	//dynamic test
	selectMenu.SelectUpdate(camera, view);
	if (isDebugModeisOn == true)
	{
		const mat3<float> debugTextNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * debugTextTransform.GetModelToWorld();
		Draw::DrawText(fontShader, debugTextNDC, debugText);
	}
	Draw::FinishDrawing();
}

void LevelTest1::Win()
{
	if (isPlayerWin == true)
	{
		Draw::draw(winpic->material);
		OBJECTFACTORY->DestroyAllObjects();
	}
}

void LevelTest1::Lose()
{
	if (isEnemyWin == true)
	{
		Draw::draw(losepic->material);
		OBJECTFACTORY->DestroyAllObjects();
	}
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

		if (isEnemyWin == false)
		{
			if (input.MatchStringWithInput() == 1)
			{
				GAMEMANAGER->SpawnUnit(knight);
				coolTime.SetKnightCoolDown();
			}
			else if (input.MatchStringWithInput() == 2)
			{
				GAMEMANAGER->SpawnUnit(archer);
				coolTime.SetArcherCoolDown();
			}
			else if (input.MatchStringWithInput() == 3)
			{
				GAMEMANAGER->SpawnUnit(magician);
				coolTime.SetMagicianCoolDown();
			}
		}
		input.SetString(L"");
		break;
	case KeyboardButton::Backspace:
		input.Erasing();
		break;
	case KeyboardButton::Num1:
		if (isEnter == false && isDebugModeisOn == true)
		{
			int random = rand() % 3;

			if (isEnemyWin == false)
			{
				if (random == 0)
				{
					GAMEMANAGER->SpawnUnit(knight);
					coolTime.SetKnightCoolDown();
				}
				else if (random == 1)
				{
					GAMEMANAGER->SpawnUnit(archer);
					coolTime.SetArcherCoolDown();
				}
				else if (random == 2)
				{
					GAMEMANAGER->SpawnUnit(magician);
					coolTime.SetMagicianCoolDown();
				}
			}
			break;
		}
		break;
	case KeyboardButton::Num2:
		if (isEnter == false && isDebugModeisOn == true)
		{
			int random = rand() % 2;

			if (random == 0)
			{
				GAMEMANAGER->SpawnUnit(skeleton);
				coolTime.SetKnightCoolDown();
			}
			else if (random == 1)
			{
				GAMEMANAGER->SpawnUnit(lich);
				coolTime.SetArcherCoolDown();
			}
			break;
		}
		break;
	case KeyboardButton::Num3:
		if (isEnter == false && isDebugModeisOn == true)
		{
			for (auto obj : GAMEMANAGER->PlayerUnits)
			{
				if (obj->GetName() != "Tower")
				{
					obj->GetComponent<UnitState>()->SetHealth(0);
				}
			}
		}
		break;
	case KeyboardButton::Num4:
		if (isEnter == false && isDebugModeisOn == true)
		{
			for (auto obj : GAMEMANAGER->EnemyUnits)
			{
				if (obj->GetName() != "Lair")
				{
					obj->GetComponent<UnitState>()->SetHealth(0);
				}
			}
		}
		break;
	case KeyboardButton::Num5:
		if (isEnter == false && isDebugModeisOn == true)
		{
			for (auto obj : GAMEMANAGER->PlayerUnits)
			{
				if (obj->GetName() != "Tower")
				{
					obj->GetComponent<UnitState>()->SetInvincibilityState(true);
				}
			}
		}
		break;
	case KeyboardButton::Num6:
		if (isEnter == false && isDebugModeisOn == true)
		{
			for (auto obj : GAMEMANAGER->PlayerUnits)
			{
				if (obj->GetName() != "Tower")
				{
					obj->GetComponent<UnitState>()->SetInvincibilityState(false);
				}
			}
		}
		break;
	case KeyboardButton::Tilde:
		if (isEnter == false)
		{
			if (isDebugModeisOn == false)
			{
				isDebugModeisOn = true;
			}
			else
			{
				isDebugModeisOn = false;
			}
		}
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
	background.transform.SetScale({ windowPoint->GetWindowWidth() * (1.f / zoom),
		windowPoint->GetWindowHeight() * (1.f / zoom) });
}

void LevelTest1::HandleScrollEvent(float scroll_amount)
{
	zoom = view.GetZoom() + (scroll_amount * 0.05f);
	zoom = std::clamp(zoom, 0.5f, 2.0f);
	background.transform.SetScale({ windowPoint->GetWindowWidth() * (1.f / zoom),
		windowPoint->GetWindowHeight() * (1.f / zoom) });
	view.SetZoom(zoom);
}

void LevelTest1::HandleMousePositionEvent(float xpos, float ypos)
{
	mousePosition = { xpos, ypos };
}
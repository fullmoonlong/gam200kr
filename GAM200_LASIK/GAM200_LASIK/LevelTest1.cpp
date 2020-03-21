/**************************************************************************************
 *	File Name        : LevelTest1.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   :
 *	Secondary Author :
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
#include "CurrencySystem.hpp"

LevelTest1::LevelTest1(OpenGLWindow* window)
{
	windowPoint = window;
	std::cout << "Add LevelTest1 Sucessful" << std::endl;
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);
	worldToNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera();
	typing.cb.Initialize(worldToNDC);
}

LevelTest1::~LevelTest1()
{
	std::cout << "Close LevelTest1 Sucessful" << std::endl;
}

void LevelTest1::Initialize()
{
	GAMEMANAGER->isGameEnd = false;
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
	typing.symbol.SetFont(bitmapFont);

	symbolTextTransform.SetTranslation(symbolPosition);

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
		tower = new Tower();
		tower->UnitInitialize("tower.txt");
		tower->material.shader = shader;
		tower->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		tower->material.texture.LoadTextureFrom(PATH::tower);
		tower->animation.Initialize({ 1,1, 1.f }, tower->material.shader);
		GAMEMANAGER->SpawnUnit(tower);
		//tower

		//lair
		lair = new Lair();
		lair->UnitInitialize("lair.txt");
		lair->material.shader = shader;
		lair->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lair->material.texture.LoadTextureFrom(PATH::lair);
		lair->animation.Initialize({ 1,1, 1.f }, lair->material.shader);
		lair->animation.Initialize({ 1, 1,	10.0f }, shader);
		GAMEMANAGER->SpawnUnit(lair);
		//lair

		skeleton = new Skeleton();
		skeleton->Initialize("skeleton.txt");
		skeleton->material.shader = shader;
		skeleton->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		skeleton->material.texture.LoadTextureFrom(PATH::skeleton_move);
		skeleton->animation.Initialize({ 4, 1,	10.0f }, shader);

		golem = new Golem();
		golem->Initialize("golem.txt");
		golem->material.shader = shader;
		golem->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		golem->material.texture.LoadTextureFrom(PATH::golem_move);
		golem->animation.Initialize({ 4, 1,	10.0f }, shader);

		lich = new Lich();
		lich->Initialize("lich.txt");
		lich->material.shader = shader;
		lich->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		lich->material.texture.LoadTextureFrom(PATH::lich_move);
		lich->animation.Initialize({ 8, 1, 10.0f }, shader);

		//knight
		knight = new Knight();
		knight->Initialize("knight.txt");
		knight->material.shader = shader;
		knight->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		knight->material.texture.LoadTextureFrom(PATH::knight_move);
		knight->animation.Initialize({ 8, 1, 10.0f }, shader);
		//knight

		//archer
		archer = new Archer();
		archer->Initialize("archer.txt");
		archer->material.shader = shader;
		archer->material.vertices.InitializeWithMeshAndLayout(rectangle, layout);
		archer->material.texture.LoadTextureFrom(PATH::archer_move);
		archer->animation.Initialize({ 8, 1, 10.0f }, shader);
		//archer

		//magician
		magician = new Magician();
		magician->Initialize("Magician.txt");
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
		swordAttack->GetComponent<BaseUnitState>()->SetDamage(knight->GetComponent<BaseUnitState>()->GetDamage());
		swordAttack->animation.Initialize({ 1,1, 1.f }, swordAttack->material.shader);

		knight->GetComponent<BaseObjectAttackComponent>()->unit = knight;
		knight->GetComponent<BaseObjectAttackComponent>()->projectile = swordAttack;
		knight->GetComponent<BaseObjectAttackComponent>()->delayTime = 0.6f;
		knight->GetComponent<BaseObjectAttackComponent>()->soundID = 3;
		knight->GetComponent<BaseObjectAttackComponent>()->startPosition.x = 48.0f;
		knight->GetComponent<BaseObjectAttackComponent>()->startPosition.y = 0.f;
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

		enemyAttack->GetComponent<BaseUnitState>()->SetDamage(skeleton->GetComponent<BaseUnitState>()->GetDamage());
		skeleton->GetComponent<BaseObjectAttackComponent>()->unit = skeleton;
		skeleton->GetComponent<BaseObjectAttackComponent>()->projectile = enemyAttack;
		skeleton->GetComponent<BaseObjectAttackComponent>()->delayTime = 0.6f;
		skeleton->GetComponent<BaseObjectAttackComponent>()->soundID = 3;
		skeleton->GetComponent<BaseObjectAttackComponent>()->startPosition.x = -48.0f;
		skeleton->GetComponent<BaseObjectAttackComponent>()->startPosition.y = 0.f;
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
		fireball->GetComponent<BaseUnitState>()->SetDamage(magician->GetComponent<BaseUnitState>()->GetDamage());

		magician->GetComponent<BaseObjectAttackComponent>()->unit = magician;
		magician->GetComponent<BaseObjectAttackComponent>()->projectile = fireball;
		magician->GetComponent<BaseObjectAttackComponent>()->delayTime = 2.4f;
		magician->GetComponent<BaseObjectAttackComponent>()->soundID = 1;
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
		fireballEnemy->GetComponent<BaseUnitState>()->SetDamage(lich->GetComponent<BaseUnitState>()->GetDamage());

		lich->GetComponent<BaseObjectAttackComponent>()->unit = lich;
		lich->GetComponent<BaseObjectAttackComponent>()->projectile = fireballEnemy;
		lich->GetComponent<BaseObjectAttackComponent>()->delayTime = 3.0f;
		lich->GetComponent<BaseObjectAttackComponent>()->soundID = 1;
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
		arrow->GetComponent<BaseUnitState>()->SetDamage(archer->GetComponent<BaseUnitState>()->GetDamage());

		archer->GetComponent<BaseObjectAttackComponent>()->unit = archer;
		archer->GetComponent<BaseObjectAttackComponent>()->projectile = arrow;
		archer->GetComponent<BaseObjectAttackComponent>()->delayTime = 0.7f;
		archer->GetComponent<BaseObjectAttackComponent>()->soundID = 2;
		//arrow
	}

	//test sound and make object
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


	typing.SetUnitPtr(knight, archer, magician, skeleton, lich);
	sidescroll.SetCameraPtr(&camera);
	//GAMEMANAGER->pg.SetNDC(cameraToNDC);	// particle generator ndc setting
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
	text.SetString(typing.GetString());
	Draw::DrawText(fontShader, textNDC, text);

	const mat3<float> symbolNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * symbolTextTransform.GetModelToWorld();
	Draw::DrawText(fontShader, symbolNDC, typing.symbol);


	coolTime.CoolDownUpdate(dt);

	//dynamic test
	for (const auto& obj : OBJECTFACTORY->GetObjectList())
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

			if (obj.second->GetName() == "lair")
			{
				obj.second->GetComponent<LairComponent>()->SpawnEnemy(skeleton, dt);
				if (obj.second->GetComponent<UnitState>()->GetHealth() <= 0)
				{
					isPlayerWin = true;
					GAMEMANAGER->isGameEnd = true;
					OBJECTFACTORY->Destroy(obj.second);
				}
			}
			else if (obj.second->GetName() == "tower")
			{
				if (obj.second->GetComponent<UnitState>()->GetHealth() <= 0)
				{
					isEnemyWin = true;
					GAMEMANAGER->isGameEnd = true;
					OBJECTFACTORY->Destroy(obj.second);
				}
			}
			else if (obj.second->GetName() == "skeleton")
			{
				if (obj.second->GetComponent<UnitState>()->GetHealth() <= 0)
				{
					cs->Increase(skeleton->GetMoney());
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
	GAMEMANAGER->pg.UpdateParticles(dt);

	typing.cb.DrawMessageBox();

	//camera.MoveRight(sideScrollSpeed);
	sidescroll.SideScroll();
	
	Draw::FinishDrawing();
}

void LevelTest1::Win()
{
	if (isPlayerWin == true)
	{
		Draw::draw(winpic->material);
		OBJECTFACTORY->DestroyAllObjects();
		GAMEMANAGER->isGameEnd = true;
	}
}

void LevelTest1::Lose()
{
	if (isEnemyWin == true)
	{
		Draw::draw(losepic->material);
		OBJECTFACTORY->DestroyAllObjects();
		GAMEMANAGER->isGameEnd = true;
	}
}

void LevelTest1::Shutdown()
{
	OBJECTFACTORY->DestroyAllObjects();
}

void LevelTest1::HandleKeyPress(KeyboardButton button)
{
	if (isPlayerWin == true || isEnemyWin == true) {
		return;
	}
	const std::wstring type = typing.GetString();
	switch (button) {
	case KeyboardButton::Enter:
		typing.Enter();
		break;
	case KeyboardButton::Arrow_Left:
	case KeyboardButton::Arrow_Right:
		sidescroll.SideScrollPress(button);
		break;
	default:
		typing.Type(button);
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
	case KeyboardButton::Arrow_Left:
	case KeyboardButton::Arrow_Right:
		sidescroll.SideScrollRelease();
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
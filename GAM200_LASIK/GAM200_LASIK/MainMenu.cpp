/**************************************************************************************
 *	File Name        : MainMenu.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : Jookyung Lee
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/


#include <iostream>
#include "MainMenu.h"
#include "StateManager.h"
#include "Sound.hpp"
#include "Engine.h"

MainMenu::MainMenu(OpenGLWindow* window)
{
	windowPoint = window;
	std::cout << "Add Mainmenu Successful\n";
}

void MainMenu::Initialize()
{
	Shader shader;
	shader.LoadTextureShader();

	view.SetViewSize(1280, 720);

	startButton.transform.SetTranslation({ 0.0f, 120.0f });
	startButton.transform.SetScale({ 500.0f, 500.0f });

	exitButton.transform.SetTranslation({ 0.0f, -120.0f });
	exitButton.transform.SetScale({ 500.0f, 500.0f });

	selectedArrow.transform.SetTranslation({ -220.0f, 120.0f });
	selectedArrow.transform.SetScale({ 70.0f, 70.0f });

	startButton.material.shader   = shader;
	exitButton.material.shader    = shader;
	selectedArrow.material.shader = shader;

	const Mesh& spriteBox = MESH::create_rectangle({ 0.0f }, { 1.0f });
	startButton.material.vertices.InitializeWithMeshAndLayout(spriteBox, layout);
	exitButton.material.vertices.InitializeWithMeshAndLayout(spriteBox, layout);
	selectedArrow.material.vertices.InitializeWithMeshAndLayout(spriteBox, layout);

	startButton.material.texture.LoadTextureFrom("../assets/StartButton.png");
	exitButton.material.texture.LoadTextureFrom("../assets/ExitButton.png");
	selectedArrow.material.texture.LoadTextureFrom("../assets/SelectArrowLeft.png");

	worldToNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera();

	startButton.material.ndc = worldToNDC * startButton.transform.GetModelToWorld();
	exitButton.material.ndc = worldToNDC * exitButton.transform.GetModelToWorld();


	SOUNDMANAGER->LoadFile("backgroundmusic.wav");
	SOUNDMANAGER->LoadFile("Fireball.wav");
	SOUNDMANAGER->LoadFile("archershoot.ogg");
}

void MainMenu::Update(float /*dt*/)
{
	Draw::StartDrawing();

	selectedArrow.transform.SetTranslation({ -220.0f, -selectedMenu * 2 * 120.0f + 120.0f });
	selectedArrow.material.ndc = worldToNDC * selectedArrow.transform.GetModelToWorld();

	Draw::draw(startButton.material);
	Draw::draw(exitButton.material);
	Draw::draw(selectedArrow.material);

	Draw::FinishDrawing();
}

void MainMenu::Shutdown()
{
	gameEngine->Shutdown();
}

void MainMenu::HandleKeyPress(KeyboardButton button)
{
	if (button == KeyboardButton::Arrow_Down) {
		--selectedMenu;
		if (selectedMenu == -1) {
			selectedArrow.transform.SetTranslation({ -100.0f, -100.0f });
			selectedMenu = 1;
		}
	}
	else if (button == KeyboardButton::Arrow_Up) {
		++selectedMenu;
		if (selectedMenu == 2) {
			exitButton.transform.SetTranslation({ -100.0f, -300.0f });
			selectedMenu = 0;
		}
	}
	else if (button == KeyboardButton::Enter)
	{
		if (selectedMenu == 0)
		{
			STATEMANAGER->SetCurrentLevel(GameLevels::LEVELSELECT);
		}
		else if (selectedMenu == 1)
		{
			gameEngine->gamestate = GameState::EXIT;
		}
	}
	else if (button == KeyboardButton::Num1)
	{
		SOUNDMANAGER->PlaySound(1, 0);
	}
	else if (button == KeyboardButton::Num2)
	{
		s -= 0.1f;
		s = std::clamp(s, 0.0f, 1.0f);
		SOUNDMANAGER->SetSystemSoundVolume(s);
	}
	else if (button == KeyboardButton::Num3)
	{
		s += 0.1f;
		s = std::clamp(s, 0.0f, 1.0f);
		SOUNDMANAGER->SetSystemSoundVolume(s);
	}
	else if (button == KeyboardButton::Num4)
	{
		SOUNDMANAGER->AllSoundStop();
	}
	else if (button == KeyboardButton::Num5)
	{
		SOUNDMANAGER->AllResume();
	}
	else if (button == KeyboardButton::Num6)
	{
		SOUNDMANAGER->PlaySound(0, 1);
	}
	else if (button == KeyboardButton::Y)
	{
		SOUNDMANAGER->DeleteAllSounds();
	}

}

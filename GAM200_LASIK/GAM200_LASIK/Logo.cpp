/**************************************************************************************
 *	File Name        : Logo.cpp
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : JeongHak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Logo.h"
#include "StateManager.h"
#include "VerticesDescriptionLayout.hpp"

Logo::Logo(OpenGLWindow* window)
{
	windowPointer = window;
	time = 0.0f;
}

void Logo::Initialize()
{
	Shader shader;
	shader.LoadTextureShader();
	view.SetViewSize(1280, 720);
	wolrdToNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera();

	digipenLogoTransform.SetScale({ 960.0f, 200.0f });
	fmodLogoTransform.SetScale({ 576.0f, 324.0f });
	teamLogoTransform.SetScale({ 576.0f, 324.0f });

	const mat3<float>& digipenLogoNDC = wolrdToNDC * digipenLogoTransform.GetModelToWorld();
	const mat3<float>& fmodLogoNDC    = wolrdToNDC * fmodLogoTransform.GetModelToWorld();
	const mat3<float>& teamLogoNDC    = wolrdToNDC * teamLogoTransform.GetModelToWorld();
	digipenLogo.CreateSprite(shader, "../assets/DigiPen_BLACK_1024px.png", digipenLogoNDC);
	fmodLogo.CreateSprite(shader, "../assets/fmod_logo.png", fmodLogoNDC);
	teamLogo.CreateSprite(shader, "../assets/TeamLogo.png", teamLogoNDC);
}

void Logo::Update(float dt)
{
	time += dt;

	Draw::StartDrawing({ 1.0f });

	if (time <= 3.0f) {
		Draw::draw(digipenLogo);
	}
	if (3.0f < time && time <= 6.0f) {
		Draw::draw(fmodLogo);
	}
	if (6.0f < time && time <= 9.0f) {
		Draw::draw(teamLogo);
	}
	if (time > 9.0f) {
		Shutdown();
	}

	Draw::FinishDrawing();
}

void Logo::Shutdown()
{
	STATEMANAGER->SetCurrentLevel(GameLevels::MAINMENU);
}

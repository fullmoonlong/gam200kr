/**************************************************************************************
 *	File Name        : Upgrade.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#pragma once

#include "LevelSystem.h"
#include "OpenGLWindow.hpp"
#include "Object.h"
#include "GetInput.hpp"
#include "EventHandler.hpp"
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Draw.hpp"
#include "BitmapFont.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "UI.hpp"

class Upgrade : public LevelSystem
{
public:
	Upgrade();
	Upgrade(OpenGLWindow* window);
	~Upgrade();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
	void HandleKeyPress(KeyboardButton button) override final;

private:
	std::wstring numberString;

	bool isUpgradeEnd;
	bool isEnter, isDebugModeisOn = false;

	GetInput input;
	OpenGLWindow* windowPoint;

	Camera camera;
	CameraView view;

	BitmapFont bitmapfont;
	Text  text, debugText, moneyText, numberText;

	Shader    spriteShader, fontShader;
	Mesh	  spriteMesh;
	Material  spriteMaterial;
	Transform spriteTransform, textTransform, debugTextTransform, moneyTransform, numberTransform;

	vec2<float> moneyPosition = { 0.0f, 50.0f };
	vec2<float> numberPosition = { 20.0f, 0.0f };
	vec2<float> spritePosition = { 0.0f, 0.0f };
	vec2<float> fontSize = { 1.5f };

	float zoom = 1.0f;
	float cameraAngle = 0.0f;
};
/**************************************************************************************
 *	File Name        : LevelSelect.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "LevelSystem.h"
#include "EventHandler.hpp"
#include "OpenGLWindow.hpp"

#include "Object.h"
#include "Util/Clock.hpp"
#include "GetInput.hpp"

#include "Camera.hpp"
#include "CameraView.hpp"
#include "Shader.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Draw.hpp"
#include "BitmapFont.hpp"

class LevelSelect : public LevelSystem {
public:
	LevelSelect(OpenGLWindow* window);
	~LevelSelect();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
	void HandleKeyPress(KeyboardButton button) override final;
	void HandleKeyRelease(KeyboardButton button) override final;

private:
	bool isEnter = false;
	bool selectStatus;
	OpenGLWindow* windowPoint;
	GetInput input, symbol;
	Draw draw;

	Text text, symbolText;
	BitmapFont bitmapfont;

	Camera camera;
	CameraView view;

	Shader    spriteShader, textShader;
	Mesh	  spriteMesh;
	Material  spriteMaterial;
	Transform spriteTransform, textTransform, symbolTextTransform;

	vec2<float> spritePosition = { 0.0f, 0.0f };
	vec2<float> symbolPosition = { -20.0f, 0.0f };
	vec2<float> pressDirection{ 0.f, 0.f };
	float zoom = 1.0f;
	float cameraAngle = 0.0f;

};
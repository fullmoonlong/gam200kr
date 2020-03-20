/**************************************************************************************
 *	File Name        : Tutorial.h
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
#include "Tower.h"
#include "Units.hpp"
#include "EnemyUnits.hpp"
#include "GetInput.hpp"
#include "Typing.hpp"
#include "UI.hpp"

#include "Camera.hpp"
#include "CameraView.hpp"
#include "Shader.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Animation.hpp"
#include "Draw.hpp"
#include "BitmapFont.hpp"
#include "Sound.hpp"
#include "CoolDown.hpp"
#include "ChatBox.hpp"
#include "SideScrolling.h"

class Tutorial : public LevelSystem {
public:
	Tutorial(OpenGLWindow* window);
	~Tutorial();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
	void TutorialEnd();
	void HandleKeyPress(KeyboardButton button) override final;
	void HandleKeyRelease(KeyboardButton button) override final;
	void HandleMouseEvent(MouseButton button) override final;
	void HandleResizeEvent(const int& new_width, const int& new_height) override;
	void HandleScrollEvent(float scroll_amount) override;
	void HandleMousePositionEvent(float xpos, float ypos) override final;

private:
	mat3<float> worldToNDC;

	bool isEnter = false;
	bool isPlayerWin;
	bool isEnemyWin;
	Shader shader;

	OpenGLWindow* windowPoint;
	Camera camera;
	CameraView view;

	GetInput input, symbol;
	//Typing type;
	SideScrolling sidescroll;

	float time;
	Object object;

	Material towerMaterial, lairMaterial;
	Mesh	 towerMesh, lairMesh;

	Object background; Shader backgroundShader; Mesh backgroundMesh; Vertices backgroundVertices; Texture backgroundTexture; 	Material backgroundMaterial;
	Object ui;
	Tower* tower;
	Lair* lair;

	Shader fontShader;
	BitmapFont bitmapFont;
	Text text, symbolText;
	Transform textTransform, lairTextTransform, towerTextTransform, symbolTextTransform;

	Knight* knight;
	Magician* magician;
	Archer* archer;
	Skeleton* skeleton;

	Object* swordAttack;
	Object* enemyAttack;
	Object* arrow;
	Object* fireball;

	CoolDown coolTime;

	UI::SelectSpawn selectMenu;
	UI::MoneyBar moneyBar;

	ChatBox cb;

	Text debugText;
	Transform debugTextTransform;

	Object* tutorialWin;
	bool win = false;
	int check = 0;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;

	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };
	mat3<float> backgroundNDC;

	vec2<float> lairExplainSize = { 600.f, 128.0f };
	vec2<float> towerExplainSize = { 700.f, 128.0f };

	vec2<float> towerPosition = { -500.0f , 80.f };
	vec2<float> lairPosition = { 500.f, 50.f };

	vec2<float> symbolPosition = { -20.0f, 0.0f };

	float sideScrollSpeed = 0.0f;

	bool isDebugModeisOn = false;

};
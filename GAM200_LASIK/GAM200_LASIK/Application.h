/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */

#pragma once
#include "OpenGL_Window.h"
#include "EventHandler.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Shader.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Animation.hpp"
#include "Draw.hpp"
#include "BitmapFont.hpp"
#include "Text.hpp"
#include "Object.h"
#include "ObjectFactory.h"
#include "Util/Clock.hpp"
#include "Sound.hpp"
#include "ObjectFactory.h"
#include "Units.hpp"
#include "GetInput.hpp"

class Application : public SimpleEventHandler
{
public:
	Application();
	~Application() = default;
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override final;
	void HandleKeyRelease(KeyboardButtons button) override final;
	void HandleMouseEvent(MouseButtons button) override final;
	void HandleResizeEvent(const int& new_width, const int& new_height) override final;
	void HandleScrollEvent(float scroll_amount) override final;
	void HandleMousePositionEvent(float xpos, float ypos) override final;
	void HandleWindowClose() override final;

	bool isRunning = false;

private:
	int frameCount = 0;
	float deltaTime = 0;
	GetInput input;

	Draw draw;
	ObjectFactory objectFactory;
	Object* proKevin;
	Object* objectTest1;

	Object background;
	Shader backgroundShader;
	Mesh backgroundMesh;
	Vertices backgroundVertices;
	Texture backgroundTexture;
	//Material backgroundMaterial;

	Shader fontShader;
	BitmapFont bitmapFont;
	Text text;
	Transform textTransform;

	Shader shader;
	Object object;
	Object object2;
	//Units
	Knight* knight;
	Magician* magician;
	Archer* archer;
	//Units

	//projectiles
	Object* swordAttack;
	Object arrow;
	Object* fireball;
	//projectiles

	//tower
	Object* tower;
	Object* lair;
	//tower

	Window window;
	Clock clock;
	
	Camera camera;
	CameraView view;

	SoundManager soundManager;
	//float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };
};

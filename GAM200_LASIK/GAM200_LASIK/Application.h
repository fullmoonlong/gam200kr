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
#include "Object.h"
#include "ObjectFactory.h"
#include "Util/Clock.hpp"
#include "Sound.hpp"
#include "ObjectFactory.h"

class Application : public SimpleEventHandler
{
public:
	Application();
	~Application() = default;
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override;
	void HandleKeyRelease(KeyboardButtons button) override;
	void HandleMouseEvent(MouseButtons button) override;
	void HandleResizeEvent(const int& width, const int& height) override;
	void HandleScrollEvent(float scroll_amount) override;
	void HandleMousePositionEvent(float xpos, float ypos) override;

	bool isRunning = false;

private:
	int frameCount = 0;
	float deltaTime = 0;

	Draw draw;

	ObjectFactory objectFactory;
	Object* objectTest;
	Object* objectTest1;

	Object object;
	ObjectFactory objFactory;

	Mesh rectangle;
	Mesh rectangle2;
	Vertices vertices;
	Vertices vertices2;
	Shader shader;
	Shader shader2;
	Animation animation;
	Animation animation2;

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

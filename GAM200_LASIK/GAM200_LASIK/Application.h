/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */


#pragma once
#include "Graphics/OpenGL_Window.h"
#include "Graphics/Shader.h"
#include "Graphics/EventHandler.hpp"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.hpp"
#include "Graphics/CameraView.hpp"
#include "Graphics/Vertices.h"
#include "Graphics/Animation.hpp"
#include "Object.h"
#include "Util/Clock.hpp"

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
	Object object;
	Mesh rectangle;
	Vertices vertices;
	Shader shader;
	Window Window;
	Clock clock;
	Animation animation;
	
	Camera camera;
	CameraView view;

	//float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };
};

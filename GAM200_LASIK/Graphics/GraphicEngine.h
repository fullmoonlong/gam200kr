/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*			Doyeong Yi doyoung.lee@digipen.edu
*	Application
*	2019/07/04
*/


#pragma once
#include <chrono>
#include <Graphics//OpenGL_Window.h>
#include <Graphics/Shader.h>
#include <Graphics/EventHandler.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Mesh.h>
#include <Graphics/Camera.hpp>
#include <Graphics/CameraView.hpp>
#include <Graphics/Transform.hpp>
#include "Object.h"

class GraphicEngine : public SimpleEventHandler
{
public:
	GraphicEngine();
	~GraphicEngine() = default;

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
	Object object1;
	Object object2;
	float timePassed = 0;
	int frameCount = 0;
	float deltaTime = 0;
	Mesh rectangle;
	Texture texture;
	Shader shader;
	glWindow glWindow;

	Camera camera;
	CameraView view;

	//float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };

};

extern GraphicEngine graphics;
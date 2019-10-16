/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*			Doyeong Yi doyoung.lee@digipen.edu
*	Application
*	2019/07/04
*/


#pragma once
#include <chrono>
#include <graphic/OpenGL_Window.h>
#include <graphic/Shader.h>
#include <graphic/EventHandler.hpp>
#include <graphic/Texture.hpp>
#include <graphic/Mesh.h>
#include <graphic/Camera.hpp>
#include <graphic/CameraView.hpp>
#include <graphic/CameraTransform.hpp>
#include "glm.hpp"

class Application : public SimpleEventHandler
{
public:
	Application();
	~Application();
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override;
	void HandleKeyRelease(KeyboardButtons button) override;
	void HandleResizeEvent(const int& width, const int& height) override;
	void HandleScrollEvent(float scroll_amount) override;

	bool isRunning = false;
	
private:
	float timePassed = 0;
	int frameCount = 0;
	std::chrono::duration<float> deltaTime;
	Mesh rectangle;
	Texture texture;
	Shader shader;
	glWindow glWindow;

	Camera camera;
	CameraView view;
	CameraTransform transform;

	//float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	glm::vec2 pressDirection{ 0.f, 0.f };
};

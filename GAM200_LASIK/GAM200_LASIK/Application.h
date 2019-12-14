/**************************************************************************************
 *	File Name        : Application.h
 *	Project Name     : Keyboard Warrior
 *	Primary Author   : Jookyung Lee
 *	Secondary Author : Wonju Cho
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "System.h"
#include "OpenGLWindow.hpp"
#include "EventHandler.hpp"
#include "Util/Clock.hpp"

class Application : public System, public SimpleEventHandler
{
public:
	Application();
	~Application() = default;
	void Initialize();
	void Update(float dt);
	void ShutDown();

	void HandleKeyPress(KeyboardButton button) override;
	void HandleKeyRelease(KeyboardButton button) override;
	void HandleMouseEvent(MouseButton button) override;
	void HandleResizeEvent(const int& new_width, const int& new_height) override;
	void HandleScrollEvent(float scroll_amount) override;
	void HandleMousePositionEvent(float xpos, float ypos) override;
	void HandleWindowClose() override;

	OpenGLWindow* GetWindow() { return &window; }
	float* GetDeltaTime() { return &deltaTime; }

	bool isRunning = false;

private:
	int frameCount = 0;
	float deltaTime = 0;

	OpenGLWindow window;
	Clock clock;
};
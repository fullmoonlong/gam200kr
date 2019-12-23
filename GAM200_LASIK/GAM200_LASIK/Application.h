/**************************************************************************************
 *	File Name        : Application.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Jookyung Lee
 *	Secondary Author : Wonju Cho
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <string>
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

	bool isRunning = false;

private:
	OpenGLWindow window;
	Clock clock;

	const std::string& windowTitle{ "Keyboard Warriors" };
	std::string windowTitleWithFrameCount;
private:
	int frameCount = 0;
};
/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Shader.h
*	
*	Header of event handler
*	
*	2019/10/03
*/

#pragma once

enum class KeyboardButtons
{
	Escape,
	F,
	V
};

enum class MouseButtons
{
	
};

class EventHandler
{
public:
	virtual void HandleKeyPress(KeyboardButtons button) = 0;
	virtual void HandleKeyRelease(KeyboardButtons button) = 0;
	virtual void HandleKeyTriggered(KeyboardButtons button) = 0;
	virtual void HandleResizeEvent(const int& width, const int& height) = 0;
	virtual void HandleWindowClose() = 0;
	bool isTriggered = false;

};

class SimpleEventHandler : EventHandler
{
public:
	void HandleKeyPress(KeyboardButtons) override {}
	void HandleKeyRelease(KeyboardButtons) override {}
	void HandleKeyTriggered(KeyboardButtons) override {}
	void HandleResizeEvent(const int& /*width*/, const int& /*height*/) override {}
	void HandleWindowClose() override {}

};
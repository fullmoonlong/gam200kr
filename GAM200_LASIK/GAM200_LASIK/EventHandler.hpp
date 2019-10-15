/*
*	Author: JeongHak Kim	junghak.kim@digipen.edu
*	
*	File_name: Shader.hpp
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
	V,
	G,
	W,
	A,
	S,
	D,
	Z,
	X
};

enum class MouseButtons
{
	
};

class EventHandler
{
public:
	virtual void HandleKeyPress(KeyboardButtons button) = 0;
	virtual void HandleKeyRelease(KeyboardButtons button) = 0;
	virtual void HandleResizeEvent(const int& width, const int& height) = 0;
	virtual void HandleScrollEvent(float scroll_amount) = 0;
	virtual void HandleWindowClose() = 0;

};

class SimpleEventHandler : public EventHandler
{
public:
	void HandleKeyPress(KeyboardButtons) override {}
	void HandleKeyRelease(KeyboardButtons) override {}
	void HandleResizeEvent(const int& /*width*/, const int& /*height*/) override {}
	void HandleScrollEvent(float /*scroll_amount*/) = 0;
	void HandleWindowClose() override {}
	
};
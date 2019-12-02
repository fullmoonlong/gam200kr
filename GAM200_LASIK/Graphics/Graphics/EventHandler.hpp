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

enum class KeyboardButton
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
	X,
	I,
	O,
	T,
	Y,
	Arrow_Left,
	Arrow_Right,
	Arrow_Up,
	Arrow_Down
};

enum class MouseButton
{
	LEFT_PRESS,
	LEFT_RELEASE
};

class EventHandler
{
public:
	virtual void HandleKeyPress(KeyboardButton button) = 0;
	virtual void HandleKeyRelease(KeyboardButton button) = 0;
	virtual void HandleResizeEvent(const int& width, const int& height) = 0;
	virtual void HandleScrollEvent(float scroll_amount) = 0;
	virtual void HandleMousePositionEvent(float xpos, float ypos) = 0;
	virtual void HandleMouseEvent(MouseButton button) = 0;
	virtual void HandleWindowClose() = 0;
	virtual void HandleFocusEvent(int focus) = 0;
};

class SimpleEventHandler : public EventHandler
{
public:
	void HandleKeyPress(KeyboardButton /*button*/) override {}
	void HandleKeyRelease(KeyboardButton /*button*/) override {}
	void HandleResizeEvent(const int& /*width*/, const int& /*height*/) override {}
	void HandleScrollEvent(float /*scroll_amount*/) override {};
	void HandleMousePositionEvent(float /*xpos*/, float /*ypos*/) override {}
	void HandleMouseEvent(MouseButton /*button*/) override {}
	void HandleWindowClose() override {}
	void HandleFocusEvent(int /*focus*/) override {}
};
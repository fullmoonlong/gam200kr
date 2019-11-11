/*
Collision.hpp
Name:Wonju cho
Date:19/10/16
*/

#pragma once
#include <iostream>
#include <GL/glew.h>
#include "Math/vec2.hpp"
#include "Graphics/OpenGL_Window.h"
#include "Graphics/Shader.h"
#include "Graphics/EventHandler.hpp"
#include "Graphics/Mesh.h"
#include "Graphics/Vertices.h"
#include "Object.h"
#include "Util/Clock.hpp"
#include "MovestateType.h"

class Collision : public SimpleEventHandler
{

public:
	bool isRunning = false;


	struct AABB {
		vec2<float> min;
		vec2<float> max;
	};

	vec2<float> speed;

	void initialize();

	Collision();

	void Update();

	void CollisionCheck();

	bool AABBvsAABB();

	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override;
	void HandleKeyRelease(KeyboardButtons button) override;
	void HandleMouseEvent(MouseButtons button) override;
	void HandleResizeEvent(const int& width, const int& height) override;
	void HandleScrollEvent(float scroll_amount) override;
	void HandleMousePositionEvent(float xpos, float ypos) override;

private:
	int frameCount = 0;
	float deltaTime = 0;

	Object player;
	Object enemy;

	Shader player_s;
	Shader enemy_s;

	MovestateType c_check;

	Window c_window;

	Clock c_clock;

	Mesh player_m;
	Mesh enemy_m;

	Vertices player_v;
	Vertices enmeny_v;

	float c_depth = 1.0f;
	float c_zoom = 1.0f;

	vec2<float> c_pressDirection{ 0.f, 0.f };
	vec2<float> c_mousePosition{ 0.f, 0.f };
};				

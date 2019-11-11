/*Coliision.cpp
Name:Wonju cho
Date:19/10/16
*/
#include "Collision.hpp"

unsigned int vbo;

void Collision::initialize()
{
	c_check = MovestateType::MOVE;
	c_window.CanCreateWindow(1024, 600, this, "Lasik");

}

Collision::Collision()
{
	initialize();
	isRunning = true;
}

void Collision::ShutDown()
{
	isRunning = false;
	glfwSetWindowShouldClose(c_window.window, GLFW_TRUE);
}

void Collision::CollisionCheck()
{
	player.Update(deltaTime);
	if(AABBvsAABB() == true)
	{
		std::cout << "fight!" << std::endl;
		c_check = MovestateType::ATTACK;
		player.speed.x = 0.0f;
	}
	else
	{
		player.speed.x = -50.0f;
	}

}

bool Collision::AABBvsAABB()
{
	Object a;
	Object b;
	if ((a.max.x < b.min.x) || (a.min.x > b.max.x) || ((a.max.y < b.min.y) || (a.min.y > b.max.y))) { return false; }

	return true;
}



void Collision::Update()
{
	c_clock.UpdateClock();

	c_window.SwapBuffers();
	c_window.PollEvents();

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw
	glUseProgram(player_s.GetHandleToShader());
	Vertices::SelecteVAO(player_v);
	glBindBuffer(GL_ARRAY_BUFFER, player_v.VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawArrays(player_v.GetPattern(), 0, (int)player_m.GetPointsCount());

	//Animation
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	//Object moving

	CollisionCheck();
	
	++frameCount;
	if (c_clock.timePassed >= 1.0f)
	{
		std::cout << frameCount << std::endl;
		c_clock.timePassed -= 1.0f;
		frameCount = 0;
	}
	deltaTime = c_clock.GetTimeFromLastUpdate();
}


void Collision::HandleKeyPress(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::Escape:
		this->ShutDown();
		break;
	case KeyboardButtons::F:
		c_window.ToggleFullScreen();
		break;
	case KeyboardButtons::V:
		if (c_window.IsVSyncOn() == false)
		{
			c_window.ToggleVSync(true);
			break;
		}
		c_window.ToggleVSync(false);
		break;
	case KeyboardButtons::W:
		break;
	case KeyboardButtons::S:
		break;
	case KeyboardButtons::A:
		break;
	case KeyboardButtons::D:
		break;
	default:;
	}
}

void Collision::HandleKeyRelease(KeyboardButtons button)
{
	switch (button)
	{
	case KeyboardButtons::W:
		c_pressDirection.y = 0;
		break;
	case KeyboardButtons::S:
		c_pressDirection.y = 0;
		break;
	case KeyboardButtons::A:
		c_pressDirection.x = 0;
		break;
	case KeyboardButtons::D:
		c_pressDirection.x = 0;
		break;
	default:;
	}
}

void Collision::HandleMouseEvent(MouseButtons button)
{
	switch (button)
	{
	case MouseButtons::LEFT_PRESS:
	{
		//mouse check
		if (player.isCollideWithMouse(c_mousePosition, c_window.GetWindowWidth(), c_window.GetWindowHeight()))
		{
			player.isMouseCollide = true;
		}
		//mouse check
		break;
	}
	case MouseButtons::LEFT_RELEASE:
		player.isMouseCollide = false;
		break;
	}
}


void Collision::HandleMousePositionEvent(float xpos, float ypos)
{
	//vec2<float> newMousePosition{ xpos, ypos };
	c_mousePosition = { xpos, ypos };
}
#pragma once

#include "OpenGLWindow.hpp"
#include "Object.h"
#include "GetInput.hpp"
#include "LevelSystem.h"
#include "EventHandler.hpp"

class Upgrade : public LevelSystem
{
public:
	Upgrade(OpenGLWindow* window);
	~Upgrade();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;
	void HandleKeyPress(KeyboardButton button) override final;

private:
	GetInput input;
	OpenGLWindow * windowPoint;
};
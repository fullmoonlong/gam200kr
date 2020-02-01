/**************************************************************************************
 *	File Name        : MainMenu.h
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : JeongHak Kim
 *	Secondary Author : Jookyung Lee
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include "LevelSystem.h"
#include "EventHandler.hpp"
#include "OpenGLWindow.hpp"

#include "Object.h"
#include "Shader.h"
#include "Mesh.h"
#include "Vertices.h"
#include "VerticesDescription.h"
#include "Draw.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"

class MainMenu : public LevelSystem {
public:
	enum MENUS {
		Start,
		Exit
	};
	MainMenu(OpenGLWindow* window);
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	void HandleKeyPress(KeyboardButton button) override final;
private:
	OpenGLWindow* windowPoint;
	Camera camera;
	CameraView view;
	int selectedMenu = Start;
	mat3<float> worldToNDC;
private:
	const VerticesDescription& layout{ VerticesDescription::Type::Point,
									   VerticesDescription::Type::TextureCoordinate };
	Object startButton;
	Object exitButton;
	Object selectedArrow;
};
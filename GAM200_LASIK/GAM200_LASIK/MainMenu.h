/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *
 *	File_name: MainMenu.h
 *
 *	MainMenu
 *
 *	Dec.13 2019
 */

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

class MainMenu : public LevelSystem {
public:
	enum MENUS {
		Start,
		Exit
	};
	MainMenu(OpenGLWindow* window);
	~MainMenu();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	void HandleKeyPress(KeyboardButton button) override final;
private:
	OpenGLWindow* windowPoint;
	Camera camera;
	CameraView view;
	Draw draw;
	int selectedMenu = Start;
	mat3<float> worldToNDC;
private:
	const VerticesDescription& layout{ VerticesDescription::Type::Point,
									   VerticesDescription::Type::TextureCoordinate };
	Object startButton;
	Object exitButton;
	Object selectedArrow;
};
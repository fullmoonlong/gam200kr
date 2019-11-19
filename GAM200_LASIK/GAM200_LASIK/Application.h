/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *			Doyeong Yi doyoung.lee@digipen.edu
 *	Application
 *	2019/07/04
 */


#pragma once
#include "OpenGL_Window.h"
#include "EventHandler.hpp"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Shader.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Animation.hpp"
#include "Draw.hpp"
#include "Object.h"
#include "Util/Clock.hpp"
#include"MovestateType.h"
#include "Units.hpp"
#include "EnemyUnits.hpp"

class Application : public SimpleEventHandler
{
public:
	Application();
	~Application() = default;
	void Initialize();
	void Update();
	void ShutDown();

	void HandleKeyPress(KeyboardButtons button) override;
	void HandleKeyRelease(KeyboardButtons button) override;
	void HandleMouseEvent(MouseButtons button) override;
	void HandleResizeEvent(const int& width, const int& height) override;
	void HandleScrollEvent(float scroll_amount) override;
	void HandleMousePositionEvent(float xpos, float ypos) override;

	bool isRunning = false;

private:
	int frameCount = 0;
	float deltaTime = 0;

	MovestateType check;
	
	//Object player;
	//Object Enemy;

	EnemyUnits::Skeleton Skeleton;
	
	//Units::Archer    Archer;
	Units::Knight    Knight;
	//Units::Magician  Magician;

	Draw draw;
	
	Shader   SkeletonShader;

	//Shader   ArcherShader;
	Shader   KnightShader;
	//Shader MagicianShader;

	Mesh SkeletonMesh;

	//Mesh ArcherMesh;
	Mesh KnightMesh;
	//Mesh MagicianMesh;

	Vertices SkeletonVertices;

	//Vertices ArcherVertices;
	Vertices KnightVertices;	
	//Vertices MaigicianVertices;

	Material SkeletonMaterial;

	//Material ArcherMaterial;
	Material KnightMaterial;
	//Material MagicianMaterial;

	Animation SkeletonAnimation;

	//Animation ArcherAnimation;
	Animation KnightAnimation;
	//Animation MagicianAnimation;

	Window window;
	Clock clock;
	
	Camera camera;
	CameraView view;

	
	//Collision collision;
	
	float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };
};

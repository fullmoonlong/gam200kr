#pragma once
#include "LevelSystem.h"
#include "EventHandler.hpp"
#include "OpenGL_Window.h"

#include "Object.h"
#include "Util/Clock.hpp"
#include "Units.hpp"
#include "GetInput.hpp"
#include "UI.hpp"

#include "Camera.hpp"
#include "CameraView.hpp"
#include "Shader.h"
#include "Vertices.h"
#include "Mesh.h"
#include "Animation.hpp"
#include "Draw.hpp"
#include "BitmapFont.hpp"

#include "Sound.hpp"

class LevelTest1 : public LevelSystem, public SimpleEventHandler
{
public:
	LevelTest1(Window* window);
	~LevelTest1();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	//void HandleKeyPress(KeyboardButton button) override final;
	//void HandleKeyRelease(KeyboardButton button) override final;
	//void HandleMouseEvent(MouseButton button) override final;
	void HandleResizeEvent(const int& new_width, const int& new_height) override;
	void HandleScrollEvent(float scroll_amount) override;
	//void HandleMousePositionEvent(float xpos, float ypos) override final;
	//void HandleWindowClose() override final;

private:
	int frameCount = 0;
	float deltaTime = 0;
	GetInput input;

	Window* windowPoint;

	Draw draw;
	Object* proKevin;
	Object* objectTest1;

	Object background;
	Shader backgroundShader;
	Mesh backgroundMesh;
	Vertices backgroundVertices;
	Texture backgroundTexture;
	//Material backgroundMaterial;

	Shader fontShader;
	BitmapFont bitmapFont;
	Text text;
	Transform textTransform;

	Shader shader;
	Shader shapeShader;
	Object object;
	Object object2;
	//Units
	Knight* knight;
	Magician* magician;
	Archer* archer;
	//Units

	//projectiles
	Object* swordAttack;
	Object arrow;
	Object* fireball;
	//projectiles

	//tower
	Object* tower;
	Object* lair;
	//tower
	Clock clock;

	Camera camera;
	CameraView view;

	SoundManager soundManager;
	//float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };
};
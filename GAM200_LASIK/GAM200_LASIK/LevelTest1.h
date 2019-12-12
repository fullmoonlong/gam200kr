#pragma once
#include "LevelSystem.h"
#include "EventHandler.hpp"
#include "OpenGLWindow.hpp"

#include "Object.h"
#include "Util/Clock.hpp"
#include "Units.hpp"
#include "EnemyUnits.hpp"
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
#include "CoolDown.hpp"
#include "Sound.hpp"

class LevelTest1 : public LevelSystem
{
public:
	LevelTest1(OpenGLWindow* window);
	~LevelTest1();
	void Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	void HandleKeyPress(KeyboardButton button) override final;
	void HandleKeyRelease(KeyboardButton button) override final;
	void HandleMouseEvent(MouseButton button) override final;
	void HandleResizeEvent(const int& new_width, const int& new_height) override;
	void HandleScrollEvent(float scroll_amount) override;
	void HandleMousePositionEvent(float xpos, float ypos) override final;
	/*void HandleWindowClose() override final;*/

private:
	bool isEnter = false;

	GetInput input;

	OpenGLWindow* windowPoint;

	Draw draw;
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
	Skeleton* skeleton;
	Lich* lich;
	Golem* golem;
	//Units

	//projectiles
	Object* swordAttack;
	Object* enemyAttack;
	Object arrow;
	Object* fireball;
	Object* fireballEnemy;
	//projectiles

	//tower
	Object* tower;
	Object* lair;
	//tower
	Clock clock;

	Camera camera;
	CameraView view;
	CoolDown coolTime;

	UI::SelectSpawn selectMenu;
	SoundManager soundManager;
	//float cameraSpeed{ 80.0f };
	float depth = 1.0f;
	float zoom = 1.0f;
	float cameraAngle = 0.0f;
	vec2<float> pressDirection{ 0.f, 0.f };
	vec2<float> mousePosition{ 0.f, 0.f };
};
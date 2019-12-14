#pragma once
#include "OpenGLWindow.hpp"
#include "EventHandler.hpp"
#include "Shader.h"
#include "Camera.hpp"
#include "CameraView.hpp"
#include "Transform.hpp"
#include "Draw.hpp"
#include "Material.hpp"

class Test : public SimpleEventHandler {
public:
	void Initialize();
	void Update();
	void ShutDown();

	bool IsRunning() const noexcept;

	void HandleKeyPress(KeyboardButton button) override;
	void HandleWindowClose() override;
private:
	const int& width = 1280;
	const int& height = 720;
	bool isRunning;

	OpenGLWindow window;
	Camera camera;
	CameraView view;
private:
	VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	Material material;
	Transform transform;
};


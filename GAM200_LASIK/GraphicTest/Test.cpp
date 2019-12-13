#include "Test.hpp"
#include "PATH.hpp"

void Test::Initialize()
{
	if (!window.CanCreateWindow(width, height, this, "Test")) {
		return;
	}
	view.SetViewSize(width, height);

	const Mesh& mesh = MESH::create_rectangle({ 0.0f }, { 1.0f });

	material.shader.LoadTextureShader();
	material.vertices.InitializeWithMeshAndLayout(mesh, layout);
	material.texture.LoadTextureFrom(PATH::knight_menu);
	transform.SetScale({ 100.0f });
	
	material.ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * transform.GetModelToWorld();
}

void Test::Update()
{
	Draw::StartDrawing();

	Draw::draw(material);

	Draw::FinishDrawing();

	window.PollEvents();
	window.SwapBuffers();
}

void Test::ShutDown()
{
	window.CleanUpWindow();
}

bool Test::IsRunning() const noexcept
{
	return isRunning;
}

void Test::HandleKeyPress(KeyboardButton button)
{
	if (button == KeyboardButton::Escape)
	{
		ShutDown();
	}
}

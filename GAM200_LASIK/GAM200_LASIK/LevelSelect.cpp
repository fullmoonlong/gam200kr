/**************************************************************************************
 *	File Name        : LevelSelect.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include "LevelSelect.h"
#include "Application.h"
#include "ObjectFactory.h"
#include "Tutorial.h"
#include "LevelTest1.h"
#include "StateManager.h"

LevelSelect::LevelSelect(OpenGLWindow* window)
{
	windowPoint = window;
}

LevelSelect::~LevelSelect()
{
}

void LevelSelect::Initialize()
{
	selectStatus = false;

	fontShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);
	text.SetFont(bitmapfont);

	const Color4f color{ 1.0f, 1.0f, 1.0f, 1.0f };
	const VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	const Mesh& rectangle = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);
	
	spriteShader.LoadShaderFrom(PATH::texture_vert, PATH::texture_frag);
	spriteMesh = rectangle;

	spriteMaterial.shader = spriteShader;
	spriteMaterial.vertices.InitializeWithMeshAndLayout(spriteMesh, layout);
	spriteMaterial.texture.LoadTextureFrom(PATH::levelSelect);
	spriteTransform.SetTranslation(spritePosition);
	spriteTransform.SetScale({ 1280,720 });
}

void LevelSelect::Update(float dt)
{
	OBJECTFACTORY->Update(dt);

	//Transform
	camera.Rotate(cameraAngle);
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);

	//Draw
	Draw::StartDrawing();

	spriteMaterial.ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * spriteTransform.GetModelToWorld();
	Draw::draw(spriteMaterial);

	const mat3<float> textNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * textTransform.GetModelToWorld();
	text.SetString(input.GetString());
	Draw::DrawText(spriteShader, textNDC, text);

	Draw::FinishDrawing();
}

void LevelSelect::Shutdown()
{
	OBJECTFACTORY->DestroyAllObjects();
}

void LevelSelect::HandleKeyPress(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::A:
		if (isEnter == true)
		{
			input.TakeAsInput('a');
			printf("a");
			break;
		}
		break;
	case KeyboardButton::B:
		if (isEnter == true)
		{
			input.TakeAsInput('b');
			printf("b");
			break;
		}
		break;
	case KeyboardButton::C:
		if (isEnter == true)
		{
			input.TakeAsInput('c');
			printf("c");
			break;
		}
		break;
	case KeyboardButton::D:
		if (isEnter == true)
		{
			input.TakeAsInput('d');
			printf("d");
			break;
		}
		break;
	case KeyboardButton::E:
		if (isEnter == true)
		{
			input.TakeAsInput('e');
			printf("e");
			break;
		}
		break;
	case KeyboardButton::F:
		if (isEnter == true)
		{
			input.TakeAsInput('f');
			printf("f");
			break;
		}
		break;
	case KeyboardButton::G:
		if (isEnter == true)
		{
			input.TakeAsInput('g');
			printf("g");
			break;
		}
		break;
	case KeyboardButton::H:
		if (isEnter == true)
		{
			input.TakeAsInput('h');
			printf("h");
			break;
		}
		break;
	case KeyboardButton::I:
		if (isEnter == true)
		{
			input.TakeAsInput('i');
			printf("i");
			break;
		}
		break;
	case KeyboardButton::J:
		if (isEnter == true)
		{
			input.TakeAsInput('j');
			printf("j");
			break;
		}
		break;
	case KeyboardButton::K:
		if (isEnter == true)
		{
			input.TakeAsInput('k');
			printf("k");
			break;
		}
		break;
	case KeyboardButton::L:
		if (isEnter == true)
		{
			input.TakeAsInput('l');
			printf("l");
			break;
		}
		break;
	case KeyboardButton::M:
		if (isEnter == true)
		{
			input.TakeAsInput('m');
			printf("m");
			break;
		}
		break;
	case KeyboardButton::N:
		if (isEnter == true)
		{
			input.TakeAsInput('n');
			printf("n");
			break;
		}
		break;
	case KeyboardButton::O:
		if (isEnter == true)
		{
			input.TakeAsInput('o');
			printf("o");
			break;
		}
		break;
	case KeyboardButton::P:
		if (isEnter == true)
		{
			input.TakeAsInput('p');
			printf("p");
			break;
		}
		break;
	case KeyboardButton::Q:
		if (isEnter == true)
		{
			input.TakeAsInput('q');
			printf("q");
			break;
		}
		break;
	case KeyboardButton::R:
		if (isEnter == true)
		{
			input.TakeAsInput('r');
			printf("r");
			break;
		}
		break;
	case KeyboardButton::S:
		if (isEnter == true)
		{
			input.TakeAsInput('s');
			printf("s");
			break;
		}
		break;
	case KeyboardButton::T:
		if (isEnter == true)
		{
			input.TakeAsInput('t');
			printf("t");
			break;
		}
		break;
	case KeyboardButton::U:
		if (isEnter == true)
		{
			input.TakeAsInput('u');
			printf("u");
			break;
		}
		break;
	case KeyboardButton::V:
		if (isEnter == true)
		{
			input.TakeAsInput('v');
			printf("v");
			break;
		}
		break;
	case KeyboardButton::W:
		if (isEnter == true)
		{
			input.TakeAsInput('w');
			printf("w");
			break;
		}
		break;
	case KeyboardButton::X:
		if (isEnter == true)
		{
			input.TakeAsInput('x');
			printf("x");
			break;
		}
		break;
	case KeyboardButton::Y:
		if (isEnter == true)
		{
			input.TakeAsInput('y');
			printf("y");
			break;
		}
		break;
	case KeyboardButton::Z:
		if (isEnter == true)
		{
			input.TakeAsInput('z');
			printf("z");
			break;
		}
		break;
	case KeyboardButton::Enter:
		if (isEnter == false)
		{
			isEnter = true;
			printf("typing start\n");
			break;
		}
		isEnter = false;
		printf("typing end\n");
		
		if (selectStatus == false)
		{
			if (input.MatchStringWithInput() == 4) //tutorial
			{
				STATEMANAGER->SetCurrentLevel(GameLevels::TUTORIAL);

			}
			else if (input.MatchStringWithInput() == 5) //level1
			{
				STATEMANAGER->SetCurrentLevel(GameLevels::LVTest1);
			}
			else if (input.MatchStringWithInput() == 6) //upgrade
			{
				STATEMANAGER->SetCurrentLevel(GameLevels::UPGRADE);
			}
		}
		input.SetString(L"");
		break;
	case KeyboardButton::Num1:
		if (isEnter == true)
		{
			input.TakeAsInput(49);
			printf("1");
			break;
		}
		break;
	case KeyboardButton::Backspace:
		input.Erasing();
		break;
	default:
		break;
	}

}

void LevelSelect::HandleKeyRelease(KeyboardButton button)
{
	switch (button)
	{
	case KeyboardButton::W:
		pressDirection.y = 0;
		break;
	case KeyboardButton::S:
		pressDirection.y = 0;
		break;
	case KeyboardButton::A:
		pressDirection.x = 0;
		break;
	case KeyboardButton::D:
		pressDirection.x = 0;
		break;
	case KeyboardButton::Z:
		cameraAngle = 0.0f;
		break;
	case KeyboardButton::X:
		cameraAngle = 0.0f;
		break;
	default:;
	}

}

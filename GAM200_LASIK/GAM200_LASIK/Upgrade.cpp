/**************************************************************************************
 *	File Name        : Upgrade.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Wonju Cho
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/
#include "Upgrade.hpp"
#include "ObjectFactory.h"
#include "CurrencySystem.hpp"
#include "UpgradeSystem.hpp"
#include "StateManager.h"

Upgrade::Upgrade()
{
}

Upgrade::Upgrade(OpenGLWindow* window)
{
	windowPoint = window;
}

Upgrade::~Upgrade()
{

}

void Upgrade::Initialize()
{
	isUpgradeEnd = false;

	spriteShader.LoadTextureShader();;
	textShader.LoadTextShader();
	bitmapfont.LoadFromFile(PATH::bitmapfont_fnt);

	text.SetFont(bitmapfont);
	symbolText.SetFont(bitmapfont);

	moneyText.SetFont(bitmapfont);
	moneyText.SetString(L"Gold ");
	
	numberText.SetFont(bitmapfont);
	numberString = std::to_wstring(cs->GetMoney());
	numberText.SetString(numberString);
	
	moneyTransform.SetTranslation(moneyPosition);
	moneyTransform.SetScale(fontSize);
	
	numberTransform.SetTranslation(numberPosition);
	numberTransform.SetScale(fontSize);

	symbolTextTransform.SetTranslation(symbolPosition);
	textTransform.SetTranslation(textPosition);

	const Color4f color{ 1.0f, 1.0f, 1.0f, 1.0f };
	const VerticesDescription layout{ VerticesDescription::Type::Point, VerticesDescription::Type::TextureCoordinate };
	const Mesh& rectangle = MESH::create_rectangle({ 0.0f }, { 1.0f }, color);

	spriteMesh = rectangle;

	spriteMaterial.shader = spriteShader;
	spriteMaterial.vertices.InitializeWithMeshAndLayout(spriteMesh, layout);
	spriteMaterial.texture.LoadTextureFrom(PATH::upgrade);
	spriteTransform.SetTranslation(spritePosition);
	spriteTransform.SetScale({ 1280,720 });

	debugTextTransform.SetTranslation({ -80.0f, 160.0f });


	debugText.SetFont(bitmapfont);
	debugText.SetString(L"debug mode");

}

void Upgrade::Update(float dt)
{
	OBJECTFACTORY->Update(dt);

	camera.Rotate(cameraAngle);
	view.SetViewSize(windowPoint->GetWindowWidth(), windowPoint->GetWindowHeight());
	view.SetZoom(zoom);

	Draw::StartDrawing();

	spriteMaterial.ndc = view.GetCameraToNDCTransform() * camera.WorldToCamera() * spriteTransform.GetModelToWorld();
	Draw::draw(spriteMaterial);

	const mat3<float> textNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * textTransform.GetModelToWorld();
	text.SetString(input.GetString());
	Draw::DrawText(textShader, textNDC, text);

	const mat3<float> symbolNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * symbolTextTransform.GetModelToWorld();
	symbolText.SetString(symbol.GetSymbolString());
	Draw::DrawText(textShader, symbolNDC, symbolText);

	const mat3<float> moneyNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * moneyTransform.GetModelToWorld();
	Draw::DrawText(textShader, moneyNDC, moneyText);
	
	numberString = std::to_wstring(cs->GetMoney());
	numberText.SetString(numberString);
	const mat3<float> numberNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * numberTransform.GetModelToWorld();
	Draw::DrawText(textShader, numberNDC, numberText);

	if (isDebugModeisOn == true) {
		const mat3<float> debugTextNDC = view.GetCameraToNDCTransform() * camera.WorldToCamera() * debugTextTransform.GetModelToWorld();
		Draw::DrawText(textShader, debugTextNDC, debugText);
	}
	Draw::FinishDrawing();
}

void Upgrade::Shutdown()
{
	OBJECTFACTORY->DestroyAllObjects();
}

void Upgrade::HandleKeyPress(KeyboardButton button)
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
			symbol.TakeAsSymbol('>');
			printf(">");
			printf("typing start\n");
			break;
		}
		isEnter = false;
		symbol.Erasing();
		printf("typing end\n");

		if (isUpgradeEnd == false)
		{
			if (input.MatchStringWithInput() == 20 && cs->GetMoney() >= 3) //arthur
			{
				up->SetKnightUpgrade(true);
				cs->Decrease(3);
			}
			else if (input.MatchStringWithInput() == 21 && cs->GetMoney() >= 5) //artemis
			{
				up->SetArcherUpgrade(true);
				cs->Decrease(5);
			}
			else if (input.MatchStringWithInput() == 22 && cs->GetMoney() >= 7) //siegfried
			{
				up->SetMagicianUpgrade(true);
				cs->Decrease(7);
			}
			else if (input.MatchStringWithInput() == 23 && cs->GetMoney() >= 4) //valkyrie
			{
				up->SetCavalryUpgrade(true);
				cs->Decrease(4);
			}
			else if (input.MatchStringWithInput() == 7) //level select menu
			{
				STATEMANAGER->SetCurrentLevel(GameLevels::LEVELSELECT);
				isUpgradeEnd = true;
			}
		}
		input.SetString(L"");
		break;
	case KeyboardButton::Backspace:
		input.Erasing();
		break;
	case KeyboardButton::Num1:
		if (isEnter == false && isDebugModeisOn == true)
		{
			cs->Increase(10);
			break;
		}
		break;
	case KeyboardButton::Tilde:
		if (isEnter == false)
		{
			if (isDebugModeisOn == false)
			{
				isDebugModeisOn = true;
			}
			else
			{
				isDebugModeisOn = false;
			}
		}
		break;
	default:
		break;
	}
}
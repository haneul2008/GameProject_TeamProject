#include<iostream>
#include<io.h>
#include<fcntl.h>
#include "DescScene.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "Transition.h"
#include "Console.h"
#include "Strings.h"

void DescScene::OnSceneEnter()
{
	system("cls");
	SetDesc();
}

void DescScene::OnSceneExit()
{
}

void DescScene::Update()
{
	Key key = InputManager::GetInstance()->getKey();
	MoveCursor(100, 30);
	cout << (int)key;
	switch (key)
	{
	case Key::ESC:
		Transition();
		SceneManager::GetInstance()->ChangeScene("TITLE");
		break;
	default:
		break;
	}
}

void DescScene::Render()
{
}

void DescScene::SetDesc()
{
	MoveCursor(2, 1);
	cout << "ESC로 돌아가기";

	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 5;
	int y = resolution.Y / 7;

	SetColor(COLOR::GRAY);
	int coutMode = _setmode(_fileno(stdout), _O_U16TEXT);
	for (const std::wstring& str : descTitle)
	{
		MoveCursor(x, y++);
		std::wcout << str;
	}
	int wcoutMode = _setmode(_fileno(stdout), coutMode);

	int halfX = resolution.X / 2 - 4;
	int halfY = resolution.Y / 2;

	y += 3;

	MoveCursor(halfX, y);
	SetColor(COLOR::LIGHT_YELLOW);
	cout << "게임 설명";

	SetColor();
	for (int i = 0; i < gameDesc.size(); ++i)
	{
		int moveX = gameDesc[i].size() / 2 - 4;
		MoveCursor(halfX - moveX, ++y);
		std::cout << gameDesc[i];
	}

	y += 5;

	MoveCursor(halfX + 2, y);
	SetColor(COLOR::LIGHT_YELLOW);
	cout << "조작법";

	SetColor();
	for (int i = 0; i < controlText.size(); ++i)
	{
		int moveX = controlText[i].size() / 2 - 4;
		MoveCursor(halfX - moveX, ++y);
		std::cout << controlText[i];
	}
}

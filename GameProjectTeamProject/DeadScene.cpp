#include<iostream>
#include "DeadScene.h"
#include "Console.h"
#include "Strings.h"
#include "InputSystem.h"
#include "Transition.h"
#include "SceneManager.h"

void DeadScene::OnSceneEnter()
{
	MoveCursor(2, 1);

	system("cls");

	std::cout << "ESC를 눌러 로비로 돌아가기";

	int x = GetConsoleResolution().X / 2 - 8;
	int y = GetConsoleResolution().Y / 3;


	for (const string& str : gameOverText)
	{
		MoveCursor(x, y++);
		std::cout << str;
	}
}

void DeadScene::OnSceneExit()
{
}

void DeadScene::Update()
{
	Key key = InputManager::GetInstance()->getKey();
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

void DeadScene::Render()
{
}

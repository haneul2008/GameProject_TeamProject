#include<iostream>
#include "DeadScene.h"
#include "Console.h"
#include "Strings.h"
#include "InputSystem.h"
#include "Transition.h"
#include "SceneManager.h"
#include "InitManager.h"
#include "UISupporter.h"
#include "InventoryManager.h"

void DeadScene::OnSceneEnter()
{
	_isDestroy = false;
}

void DeadScene::OnSceneExit()
{
}

void DeadScene::Update()
{
	if (_isDestroy == false)
	{
		_isDestroy = true;
		InitManager::GetInstance()->DeletePlayer();
		UISupporter::GetInstance()->removeUI(HP_UI);
		RenderScene();
	}

	Key key = InputManager::GetInstance()->getKeyFast();
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

void DeadScene::RenderScene()
{
	system("cls");

	MoveCursor(2, 1);
	std::cout << "ESC를 눌러 로비로 돌아가기";

	int x = GetConsoleResolution().X / 2 - 8;
	int y = GetConsoleResolution().Y / 3;


	for (const string& str : gameOverText)
	{
		MoveCursor(x, y++);
		std::cout << str;
	}
}

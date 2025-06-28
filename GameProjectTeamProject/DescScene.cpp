#include "DescScene.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "Transition.h"

void DescScene::OnSceneEnter()
{
	system("cls");
}

void DescScene::OnSceneExit()
{
}

void DescScene::Update()
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

void DescScene::Render()
{
}

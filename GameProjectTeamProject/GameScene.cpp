#include "Console.h"
#include "GameScene.h"
#include "StageManager.h"

void GameScene::OnSceneEnter()
{
	//Temp
	SetConsoleFont(L"", { 14,14 }, 1);
	SetConsoleSetting(800, 600, true, L"Game");
	
	StageManager::GetInstance()->CreateMap();
}

void GameScene::OnSceneExit()
{
	system("cls");
}

void GameScene::Update()
{
}

void GameScene::Render()
{
	StageManager::GetInstance()->Render();
}

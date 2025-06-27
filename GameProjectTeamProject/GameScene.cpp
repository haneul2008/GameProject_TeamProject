#include "Console.h"
#include "GameScene.h"
#include "StageManager.h"
#include"InitManager.h"

void GameScene::OnSceneEnter()
{
	//Temp
	SetConsoleFont(L"", { 18,18 }, 1);
	SetConsoleSetting(800, 600, true, L"Game");
	
	StageManager::GetInstance()->CreateMap();
	InitManager::GetInstance()->InitPlayer();
}

void GameScene::OnSceneExit()
{
	InitManager::GetInstance()->DeletePlayer();
	system("cls");
}

void GameScene::Update()
{
}

void GameScene::Render()
{
	StageManager::GetInstance()->Render();
}

#include "GameScene.h"
#include "StageManager.h"
#include"InitManager.h"

void GameScene::OnSceneEnter()
{
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

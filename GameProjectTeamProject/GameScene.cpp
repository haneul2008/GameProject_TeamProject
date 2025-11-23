#include "GameScene.h"
#include "StageManager.h"
#include"InitManager.h"
#include"EntityManager.h"
#include"InputSystem.h"	

void GameScene::OnSceneEnter()
{
	StageManager::GetInstance()->Init();
	StageManager::GetInstance()->CreateMap();

	InitManager::GetInstance()->InitPlayer();
	InitManager::GetInstance()->InitEnemies();
	InitManager::GetInstance()->InitItems();

	StageManager::GetInstance()->SpawnObjects();
}

void GameScene::OnSceneExit()
{
	InitManager::GetInstance()->RemovePlayer();

	EntityManager::GetInstance()->deleteAllActiveObject();

	InitManager::GetInstance()->RemoveEnemies();
	InitManager::GetInstance()->RemoveItems();

	system("cls");
}

void GameScene::Update()
{
}

void GameScene::Render()
{
	StageManager::GetInstance()->Render();
}

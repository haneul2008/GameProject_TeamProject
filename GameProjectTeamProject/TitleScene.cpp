#include "TitleScene.h"
#include "Console.h"

void TitleScene::OnSceneEnter()
{
	SetConsoleFont(L"", { 12,12 }, 1);
	SetConsoleSetting(800, 600, true, L"Game");
}

void TitleScene::OnSceneExit()
{
}

void TitleScene::Update()
{
}

void TitleScene::Render()
{
}

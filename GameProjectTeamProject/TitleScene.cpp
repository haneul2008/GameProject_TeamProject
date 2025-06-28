#include<iostream>
#include<io.h>
#include<fcntl.h>
#include<string>
#include "TitleScene.h"
#include "Console.h"
#include "Strings.h"

void TitleScene::OnSceneEnter()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 5;
	int y = resolution.Y / 4;

	int coutMode = _setmode(_fileno(stdout), _O_U16TEXT);
	for (const std::wstring& str : title)
	{
		MoveCursor(x, y++);
		std::wcout << str;
	}
	int wcoutMode = _setmode(_fileno(stdout), coutMode);

	std::vector<Pos> posList;

	posList.push_back({ resolution.X / 2 - 4, y + 5 });
	MoveCursor(posList[0].x, posList[0].y);
	std::cout << "게임 시작";

	posList.push_back({ resolution.X / 2 - 4, y + 10 });
	MoveCursor(posList[1].x, posList[1].y);
	std::cout << "게임 설명";

	posList.push_back({ resolution.X / 2 - 4, y + 15 });
	MoveCursor(posList[2].x, posList[2].y);
	std::cout << "게임 종료";

	_titleInteraction = new TitleInteraction(posList);
}

void TitleScene::OnSceneExit()
{
	delete _titleInteraction;
}

void TitleScene::Update()
{
	_titleInteraction->Update();
}

void TitleScene::Render()
{
}
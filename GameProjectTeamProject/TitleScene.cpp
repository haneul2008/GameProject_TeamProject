#include<iostream>
#include<io.h>
#include<fcntl.h>
#include<string>
#include "TitleScene.h"
#include "Console.h"
#include "Strings.h"
#include "DataSaver.h"

void TitleScene::OnSceneEnter()
{
	COORD resolution = GetConsoleResolution();
	int x = resolution.X / 5;
	int y = resolution.Y / 4;

	SetColor(COLOR::GRAY);
	int coutMode = _setmode(_fileno(stdout), _O_U16TEXT);
	for (const std::wstring& str : title)
	{
		MoveCursor(x, y++);
		std::wcout << str;
	}
	int wcoutMode = _setmode(_fileno(stdout), coutMode);

	std::vector<Pos> posList;

	SetColor();

	string str[3] = {
		"게임 시작",
		"게임 설명",
		"게임 종료"
	};

	for(int i = 0; i < 3; ++i)
	{
		posList.push_back({ resolution.X / 2 - 4, y + 5 * (i + 1) });
		MoveCursor(posList[i].x, posList[i].y);
		std::cout << str[i];
	}

	MoveCursor(posList[2].x - 3, posList[2].y + 7);
	SetColor(COLOR::LIGHT_BLUE);
	std::cout << "최고 깊이 : " << DataSaver().GetBestScore() << "층";

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
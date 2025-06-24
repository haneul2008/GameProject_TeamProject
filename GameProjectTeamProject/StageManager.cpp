#include<iostream>
#include<string>
#include<vector>
#include "StageManager.h"
#include "Enums.h"
#include "Console.h"
#include "RoomRender.h"

using std::cout;
using std::endl;
using std::vector;

inline void StageManager::Update()
{
}

inline void StageManager::Render()
{
	MoveCursor(0, 0);
	RenderStage();
}

int StageManager::GetUpdatePriotity()
{
	return 10;
}

int StageManager::GetRenderPriotity()
{
	return 10;
}

void StageManager::RenderStage()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			if (_stage->curMap[i][j] == (char)Tile::WALL)
				cout << "¡á"; // º®
			else if (_stage->curMap[i][j] == (char)Tile::ROAD)
				cout << "¡¤"; // ±æ
			else if (_stage->curMap[i][j] == (char)Tile::START)
				cout << "¡Ù"; // ½ÃÀÛ Æ÷Å»
			else if (_stage->curMap[i][j] == (char)Tile::GOAL)
				cout << "¢Ç"; // ¸ñÇ¥ Æ÷Å»
			else
				cout << "  ";
		}

		cout << endl;
	}
}

StageManager::StageManager()
{
	SetConsoleFont(L"", {12,12}, 1);
	SetConsoleSetting(800, 600, true, L"Game");

	_stage = new STAGE;
	_stage->curMap = new char[MAP_HEIGHT][MAP_WIDTH];
	_roomRender = new RoomRender;
	_roomGenerator = new RoomGenerator(3);

	CreateMap();
}

StageManager::~StageManager()
{
	delete[] _stage->curMap;
	delete[] _stage;
	delete[] _roomRender;
	delete[] _roomGenerator;
}

PSTAGE StageManager::GetStage()
{
	return _stage;
}

void StageManager::CreateMap()
{
	_rooms = _roomGenerator->GenerateRooms(_stage);

	for (const PROOM room : _rooms)
		_roomRender->DrawRoom(_stage, room);
}

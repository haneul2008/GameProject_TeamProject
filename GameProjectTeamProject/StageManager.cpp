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
			cout << _stage->curMap[i][j].symbol;
		}

		cout << endl;
	}
}

StageManager::StageManager()
{
	SetConsoleFont(L"", {12,12}, 1);
	SetConsoleSetting(800, 600, true, L"Game");

	_stage = new STAGE;
	_stage->curMap = new RenderTile[MAP_HEIGHT][MAP_WIDTH];
	_roomRender = new RoomRender(_stage);
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
	RoomInfo info = _roomGenerator->GenerateRooms(_stage);
	_rooms = info.rooms;
	vector<vector<Pos>>* pathList = &info.pathList;
	for (const PROOM room : _rooms)
		_roomRender->DrawRoom(_stage, room);

	for (const vector<Pos> path : *pathList)
		_roomRender->DrawPath(_stage, path);
}

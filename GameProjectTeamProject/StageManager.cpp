#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
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
				cout << "  "; // ±æ
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

StageManager::StageManager() : _rooms()
{
	SetConsoleFont(L"", {12,12}, 1);
	SetConsoleSetting(800, 600, true, L"Game");
	ShowCursor(false);

	_stage = new STAGE;
	_stage->curMap = new char[MAP_HEIGHT][MAP_WIDTH];
	_roomRender = new RoomRender;

	CreateMap();
}

StageManager::~StageManager()
{
	delete[] _stage->curMap;
	delete[] _stage;
	delete[] _roomRender;

	for (const auto& room : _rooms)
	{
		delete room;
	}
}

PSTAGE StageManager::GetStage()
{
	return _stage;
}

void StageManager::CreateMap()
{
	for (const auto& room : _rooms)
	{
		delete room;
	}

	_rooms.clear();
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_ROOM; ++i)
	{
		PROOM newRoom = new ROOM;
		newRoom->width = rand() % MAX_ROOM_WIDTH + MIN_ROOM_WIDTH;
		newRoom->height = rand() % MAX_ROOM_HEIGHT + MIN_ROOM_HEIGHT;
		newRoom->x = rand() % (MAP_WIDTH - newRoom->width);
		newRoom->y = rand() % (MAP_HEIGHT - newRoom->height);
		bool isContinue = false;

		for (const auto& room : _rooms)
		{
			if (room->IsOverlap(*newRoom))
			{
				delete newRoom;
				isContinue = true;
				break;
			}
		}

		if (isContinue) continue;

		_rooms.push_back(newRoom);
	}

	for (const auto& room : _rooms)
	{
		_roomRender->DrawRoom(_stage, room);
	}

	int randNum = rand() % _rooms.size();

	_stage->startPos = _rooms[randNum]->GetCenter();
	_stage->endPos = _rooms[((randNum + 1) % _rooms.size())]->GetCenter();

	COORD startPos = _stage->startPos;
	COORD endPos = _stage->endPos;

	_stage->curMap[startPos.Y][startPos.X] = (char)Tile::START;
	_stage->curMap[endPos.Y][endPos.X] = (char)Tile::GOAL;
}

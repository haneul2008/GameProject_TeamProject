#include<iostream>
#include<string>
#include<vector>
#include "StageManager.h"
#include "Enums.h"
#include "Console.h"
#include "RoomRender.h"
#include "Physics.h"
#include "Entity.h"
#include "Transition.h"

using std::cout;
using std::endl;
using std::vector;

StageManager::StageManager()
{
	_stage = new STAGE;
	_stage->curMap = new RenderTile[MAP_HEIGHT][MAP_WIDTH];
	_roomRender = new RoomRender(_stage);
	_roomGenerator = new RoomGenerator(3);
}

StageManager::~StageManager()
{
	delete[] _stage->curMap;

	for (const PROOM room : _stage->rooms)
		delete room;

	delete[] _stage;
	delete[] _roomRender;
	delete[] _roomGenerator;
}

void StageManager::CreateMap()
{
	RoomInfo info = _roomGenerator->GenerateRooms(_stage);
	_stage->rooms = std::move(info.rooms);
	vector<vector<Pos>>* pathList = &info.pathList;
	for (const PROOM room : _stage->rooms)
		_roomRender->DrawRoom(_stage, room);

	for (Path& path : *pathList)
		_roomRender->DrawPath(_stage, path);
}

void StageManager::Render()
{
	MoveCursor(0, 0);
	RenderStage();
}

PSTAGE StageManager::GetStage()
{
	return _stage;
}

bool StageManager::CheckGoal(const Pos& pos)
{
	if (_stage->endPos == pos)
	{
		ClearStage();
		CreateMap();
		Transition();
		return true;
	}

	return false;
}

void StageManager::RenderStage()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			Collider* collider = PhysicsManager::GetInstance()->getCollider({ j, i });
			if (dynamic_cast<Entity*>(collider) != nullptr)
			{
				MoveCursor(collider->getPosition()->x * 2 + 2, collider->getPosition()->y);
				continue;
			}

			if (_stage->curMap[i][j].isHide)
				cout << "  ";
			else
			{
				SetColor(_stage->curMap[i][j].textColor);
				cout << _stage->curMap[i][j].symbol;
			}
		}

		cout << endl;
	}
}

void StageManager::ClearStage()
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			_stage->curMap[i][j].isHide = true;
			_stage->curMap[i][j].SetTile(Tile::EMPTY);
		}

		cout << endl;
	}
}

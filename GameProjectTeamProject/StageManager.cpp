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
#include "Random.h"
#include "DataSaver.h"

using std::cout;
using std::endl;
using std::vector;

StageManager::StageManager()
{
	_stage = new STAGE;
	_stage->curMap = new RenderTile[MAP_HEIGHT][MAP_WIDTH];
	_roomRender = new RoomRender(_stage);
	_roomGenerator = new RoomGenerator(3);
	_objectSpawner = new ObjectSpawner(_stage);
	_currentFloor = 0;
}

StageManager::~StageManager()
{
	delete[] _stage->curMap;

	for (const PROOM room : _stage->rooms)
		delete room;

	delete[] _roomRender;
	delete[] _roomGenerator;
	delete[] _objectSpawner;
	delete[] _stage;
}

void StageManager::Init()
{
	_currentFloor = 0;
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
		DataSaver().SetBestScore(++_currentFloor);

		ClearStage();
		CreateMap();
		Transition();
		return true;
	}

	return false;
}

void StageManager::SpawnObjects()
{
	Random random;

	_objectSpawner->SetUp();

	string poolName = "ENEMY";
	int cnt = random.GetRandomPoint(MIN_ENEMY, MAX_ENEMY);

	for(int i = 0; i < cnt; ++i)
		_objectSpawner->Spawn(poolName);
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

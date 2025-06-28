#pragma once
#include<vector>
#include"IUpdate.h"
#include"IRender.h"
#include"Singletone.h"
#include"Object.h"
#include"Types.h"
#include"Constants.h"
#include"RoomGenerator.h"
#include"ObjectSpawner.h"
#include "Physics.h"

using std::vector;

class RoomRender;

class StageManager : public Singleton<StageManager>
{
public:
	StageManager();
	~StageManager();
public:
	void Init();
	void CreateMap();
	void Render();
	PSTAGE GetStage();
	bool CheckGoal(const Pos& pos);
	void SpawnObjects();
private:
	void RenderStage();
	void ClearStage();
private:
	PSTAGE _stage;
	RoomRender* _roomRender;
	RoomGenerator* _roomGenerator;
	ObjectSpawner* _objectSpawner;
	std::vector<Collider*> _colliders;
	int _currentFloor;
};
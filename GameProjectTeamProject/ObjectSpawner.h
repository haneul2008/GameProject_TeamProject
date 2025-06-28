#pragma once
#include<unordered_map>
#include<vector>
#include"Object.h"
#include"Types.h"

class ObjectSpawner
{
public:
	ObjectSpawner(PSTAGE stage);
public:
	void Spawn(Object* object);
private:
	int GetRandomPoint(int start, int end);
private:
	PSTAGE _stage;
	std::unordered_map<PROOM, std::vector<Pos>> _spawnPosPairs;
};


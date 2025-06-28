#pragma once
#include<unordered_map>
#include<vector>
#include<string>
#include"Object.h"
#include"Types.h"

class ObjectSpawner
{
public:
	ObjectSpawner(PSTAGE stage);
public:
	void SetUp();
	Object* Spawn(std::string poolName);
private:
	PSTAGE _stage;
	std::unordered_map<PROOM, std::vector<Pos>> _spawnPosPairs;
};


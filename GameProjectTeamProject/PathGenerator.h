#pragma once
#include<vector>
#include<map>
#include<set>
#include"StageManager.h"
#include"Object.h"

typedef vector<Pos> PATH;

class PathGenerator
{
public:
	PathGenerator(const vector<PROOM>& rooms, PSTAGE stage);
private:
	PROOM GetNearestRoom(const vector<PROOM>& rooms, PROOM room);
	PATH CalculatePath(PROOM startRoom, PROOM endRoom);
};
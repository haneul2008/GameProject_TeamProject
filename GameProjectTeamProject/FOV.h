#pragma once
#include<vector>
#include"Object.h"
#include"Types.h"

class FOV
{
public:
	FOV(PSTAGE stage, std::vector<PROOM> rooms) :_stage(stage), _rooms(rooms) {};
public:
	void UpdateFov(const Pos& targetPos);
private:
	PSTAGE _stage;
	std::vector<PROOM> _rooms;
};
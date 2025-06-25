#pragma once
#include<vector>
#include"StageManager.h"

class RoomRender
{
public:
	void DrawRoom(const PSTAGE stage, const PROOM room) const;
	void DrawPath(const PSTAGE stage, const std::vector<Pos>& pathList);
};


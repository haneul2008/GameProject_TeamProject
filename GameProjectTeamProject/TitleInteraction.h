#pragma once
#include<vector>
#include"Object.h"
class TitleInteraction
{
public:
	TitleInteraction(std::vector<Pos> posList);
public:
	void Update();
private:
	void RenderSword();
	void Interact();
private:
	std::vector<Pos> _posList;
	Pos _prevPos;
	int _selectIdx;
};
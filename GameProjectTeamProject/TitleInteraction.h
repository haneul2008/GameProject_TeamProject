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
	std::pair<Pos, Pos> _prevPosPair;
	int _selectIdx;
};
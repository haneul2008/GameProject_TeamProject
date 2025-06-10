#pragma once
#include"IUpdate.h"

struct Pos
{
	int x;
	int y;
};

class Stage : public IUpdate
{
	void Update() override;
	int GetPriotity() override;
};
#pragma once
#include"IUpdate.h"

const int MAP_WIDTH = 61;
const int MAP_HEIGHT = 60;

class Stage : public IUpdate
{
public:
	void Update() override;
	int GetPriotity() override;
	void RenderStage();
public:
	Stage();
	~Stage();
private:
	char(*_curMap)[MAP_WIDTH];
};
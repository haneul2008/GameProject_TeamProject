#pragma once
#include<vector>
#include "Core.h"
#include "IRender.h"

using std::vector;

class RenderContainer
{
public:
	RenderContainer();
	~RenderContainer();
private:
	vector<IRender*> _renders;
};


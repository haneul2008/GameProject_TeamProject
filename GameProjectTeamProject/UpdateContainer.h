#pragma once
#include<vector>
#include "Core.h"

using std::vector;

class UpdateContainer
{
public:
	UpdateContainer();
	~UpdateContainer();
private:
	vector<IUpdate*> _updates;
};


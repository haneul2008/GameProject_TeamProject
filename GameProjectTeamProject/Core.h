#pragma once
#include<vector>
#include"IUpdate.h"

using std::vector;

class Core
{
public:
	void Run();
	void AddUpdate(IUpdate& update);
private:
	vector<IUpdate> _updateList;
	void Update();
	void Render();
	bool UpdatePredicate(IUpdate& prev, IUpdate& current);
private:
	int m_hp;
};


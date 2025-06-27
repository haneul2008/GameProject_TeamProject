#pragma once
#include<vector>
#include"IUpdate.h"
#include"IRender.h"
#include"Singletone.h"

using std::vector;

class Core : public Singleton<Core>
{
public:
	void Run();
	void AddUpdate(IUpdate* update);
	void AddRender(IRender* render);
	void RemoveUpdate(IUpdate* update);
	void RemoveRender(IRender* render);
private:
	vector<IUpdate*> _updateList;
	vector<IRender*> _renderList;
	void Update();
	void Render();
	static bool UpdatePredicate(IUpdate* prev, IUpdate* current);
	static bool RenderPredicate(IRender* a, IRender* b);
private:
	int m_hp;
};


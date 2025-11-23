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
	void QuitGame();
private:
	vector<IUpdate*> _updateList;
	vector<IRender*> _renderList;
	void Update();
	void Render();
	static bool UpdatePredicate(IUpdate* prev, IUpdate* current);
	static bool RenderPredicate(IRender* a, IRender* b);
	// 끔찍하지만 시간상의 문제로 어쩔 수 없음. 개선 필요.
public:
	void setPlayerDead(bool isDead);
private:
	bool _isRunning;
	int m_hp;
	bool m_playerDead;
};


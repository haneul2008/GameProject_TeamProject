#pragma once
#include"Scene.h"

class DeadScene : public Scene
{
public:
	// Scene��(��) ���� ��ӵ�
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
private:
	void RenderScene();
private:
	bool _isDestroy;
};


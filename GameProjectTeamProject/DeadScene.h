#pragma once
#include"Scene.h"

class DeadScene : public Scene
{
	// Scene��(��) ���� ��ӵ�
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
};


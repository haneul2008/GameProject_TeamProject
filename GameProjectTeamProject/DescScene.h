#pragma once
#include"Scene.h"

class DescScene : public Scene
{
	// Scene��(��) ���� ��ӵ�
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
};


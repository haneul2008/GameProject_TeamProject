#pragma once
#include"Scene.h"

class DescScene : public Scene
{
public:
	// Scene��(��) ���� ��ӵ�
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
private:
	void SetDesc();
};


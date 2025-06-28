#pragma once
#include"Scene.h"

class DeadScene : public Scene
{
	// Scene을(를) 통해 상속됨
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
};


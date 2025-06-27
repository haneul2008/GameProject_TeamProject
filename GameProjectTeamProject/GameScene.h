#pragma once
#include"Scene.h"

class GameScene : public Scene
{
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
};


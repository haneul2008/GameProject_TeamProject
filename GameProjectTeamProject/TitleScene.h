#pragma once
#include"Scene.h"

class TitleScene : public Scene
{
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
};


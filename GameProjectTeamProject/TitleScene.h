#pragma once
#include<vector>
#include"Scene.h"
#include"Object.h"
#include "TitleInteraction.h"

class TitleScene : public Scene
{
public:
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
private:
	TitleInteraction* _titleInteraction;
};


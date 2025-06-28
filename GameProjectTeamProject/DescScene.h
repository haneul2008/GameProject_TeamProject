#pragma once
#include"Scene.h"

class DescScene : public Scene
{
public:
	// Scene을(를) 통해 상속됨
	void OnSceneEnter() override;
	void OnSceneExit() override;
	void Update() override;
	void Render() override;
private:
	void SetDesc();
};


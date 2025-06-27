#pragma once
#include<string>

class Scene
{
public:
	virtual void OnSceneEnter() abstract;
	virtual void OnSceneExit() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
};


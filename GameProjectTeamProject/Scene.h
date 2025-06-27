#pragma once
#include<string>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;
public:
	virtual void OnSceneEnter() abstract;
	virtual void OnSceneExit() abstract;
	virtual void Update() abstract;
	virtual void Render() abstract;
};


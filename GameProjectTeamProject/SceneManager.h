#pragma once
#include<unordered_map>
#include<string>
#include"Scene.h"
#include"Singletone.h"
#include"IUpdate.h"
#include"IRender.h"

class SceneManager : public Singleton<SceneManager>, public IUpdate, public IRender
{
public:
	SceneManager();
	~SceneManager();
public:
	void ChangeScene(std::string sceneName);
public:
	void Update() override;
	int GetUpdatePriotity() override;

	void Render() override;
	int GetRenderPriotity() override;
private:
	Scene* _currentScene;
	std::unordered_map<std::string, Scene*> _scenePairs;
};


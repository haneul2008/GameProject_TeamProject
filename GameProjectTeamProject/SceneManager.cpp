#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneManager::SceneManager() : _scenePairs(), _currentScene(nullptr)
{
	_scenePairs["TITLE"] = new TitleScene;
	_scenePairs["GAME"] = new GameScene;

	ChangeScene("TITLE");
}

SceneManager::~SceneManager()
{
	_currentScene = nullptr;
	for (const auto& scene : _scenePairs)
		delete scene.second;

	_scenePairs.clear();
}

void SceneManager::ChangeScene(std::string sceneName)
{
	if (_currentScene != nullptr)
		_currentScene->OnSceneExit();

	_currentScene = _scenePairs[sceneName];
	_currentScene->OnSceneEnter();
}

void SceneManager::Update()
{
	if (_currentScene != nullptr)
		_currentScene->Update();
}

int SceneManager::GetUpdatePriotity()
{
	return 20;
}

void SceneManager::Render()
{
	if (_currentScene != nullptr)
		_currentScene->Render();
}

int SceneManager::GetRenderPriotity()
{
	return 20;
}

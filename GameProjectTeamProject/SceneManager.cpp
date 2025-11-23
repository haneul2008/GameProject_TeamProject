#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "DescScene.h"
#include "DeadScene.h"

SceneManager::SceneManager() : _scenePairs(), _currentScene(nullptr), _currentSceneName("")
{
	_scenePairs["TITLE"] = new TitleScene;
	_scenePairs["GAME"] = new GameScene;
	_scenePairs["DESC"] = new DescScene;
	_scenePairs["DEAD"] = new DeadScene;

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

	_currentSceneName = sceneName;
	_currentScene = _scenePairs[sceneName];
	_currentScene->OnSceneEnter();
}

std::string SceneManager::GetCurrentSceneName()
{
	return _currentSceneName;
}

void SceneManager::Update()
{
	if (_currentScene != nullptr)
		_currentScene->Update();
}

void SceneManager::Render()
{
	if (_currentScene != nullptr)
		_currentScene->Render();
}

int SceneManager::GetUpdatePriotity()
{
	return 20;
}

int SceneManager::GetRenderPriotity()
{
	return 20;
}

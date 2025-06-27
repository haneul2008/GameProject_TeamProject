#include "UpdateContainer.h"
#include "SceneManager.h"

UpdateContainer::UpdateContainer()
{
	_updates.push_back(SceneManager::GetInstance());

	for (IUpdate* update : _updates)
	{
		Core::GetInstance()->AddUpdate(update);
	}
}

UpdateContainer::~UpdateContainer()
{
	for (IUpdate* update : _updates)
	{
		Core::GetInstance()->RemoveUpdate(update);
		if (dynamic_cast<SceneManager*>(update) == nullptr)
			delete update;
	}
}
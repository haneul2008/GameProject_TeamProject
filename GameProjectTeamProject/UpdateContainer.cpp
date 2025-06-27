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
		delete update;
	}
}
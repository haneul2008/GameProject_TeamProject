#include "UpdateContainer.h"
#include "StageManager.h"

UpdateContainer::UpdateContainer()
{
	_updates.push_back(StageManager::GetInstance());

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

#include "UpdateContainer.h"
#include "Stage.h"

UpdateContainer::UpdateContainer()
{
	_updates.push_back(new Stage);

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

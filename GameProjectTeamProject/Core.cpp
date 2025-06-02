#include<algorithm>
#include "Core.h"

void Core::Run()
{
	while (true)
	{
		Update();
		Render();
		
		// FrameSync()
	}
}

void Core::AddUpdate(IUpdate& update)
{
	_updateList.push_back(update);
	std::sort(_updateList.begin(), _updateList.end(), UpdatePredicate);
}

void Core::Update()
{
	for (IUpdate& update : _updateList)
	{
		update.Update();
	}
}

void Core::Render()
{
}

bool Core::UpdatePredicate(IUpdate& a, IUpdate& b)
{
	return a.GetPriotity() > b.GetPriotity();
}

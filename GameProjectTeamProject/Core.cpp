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

void Core::AddUpdate(IUpdate* update)
{
	_updateList.push_back(update);
	std::sort(_updateList.begin(), _updateList.end(), UpdatePredicate);
}

void Core::AddRender(IRender* render)
{
	_renderList.push_back(render);
	std::sort(_renderList.begin(), _renderList.end(), RenderPredicate);
}

void Core::Update()
{
	for (IUpdate* update : _updateList)
	{
		update->Update();
	}
}

void Core::Render()
{
	for (IRender* render : _renderList)
	{
		render->Render();
	}
}

bool Core::UpdatePredicate(IUpdate* a, IUpdate* b)
{
	return a->GetUpdatePriotity() > b->GetUpdatePriotity();
}

bool Core::RenderPredicate(IRender* a, IRender* b)
{
	return a->GetRenderPriotity() > b->GetRenderPriotity();
}

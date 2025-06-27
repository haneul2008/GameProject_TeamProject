#include<algorithm>
#include "Core.h"
#include "Console.h"

void Core::Run()
{
	_isRunning = true;

	while (true)
	{
		Update();
		Render();
		
		FrameSync(5);

		if (_isRunning == false) break;
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

void Core::RemoveUpdate(IUpdate* update)
{
	auto it = std::remove(_updateList.begin(), _updateList.end(), update);
	_updateList.erase(it, _updateList.end());
}

void Core::RemoveRender(IRender* render)
{
	auto it = std::remove(_renderList.begin(), _renderList.end(), render);
	_renderList.erase(it, _renderList.end());
}

void Core::QuitGame()
{
	_isRunning = false;
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

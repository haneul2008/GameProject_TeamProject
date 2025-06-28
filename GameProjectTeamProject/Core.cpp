#include<algorithm>
#include "Core.h"
#include "Console.h"
#include "Entity.h"

void Core::Run()
{
	_isRunning = true;

	while (true)
	{
		Update();
		Render();
		
		FrameSync(300);

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
	for(int i = 0; i < _updateList.size(); ++i)
	{
		_updateList[i]->Update();
	}
}

void Core::Render()
{
	for(int i = 0; i < _renderList.size(); ++i)
	{
		_renderList[i]->Render();
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

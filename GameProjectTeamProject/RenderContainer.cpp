#include "RenderContainer.h"
#include "StageManager.h"

RenderContainer::RenderContainer()
{
	_renders.push_back(StageManager::GetInstance());

	for (IRender* render : _renders)
	{
		Core::GetInstance()->AddRender(render);
	}
}

RenderContainer::~RenderContainer()
{
	for (IRender* render : _renders)
	{
		delete render;
	}
}

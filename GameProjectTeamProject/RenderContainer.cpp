#include "RenderContainer.h"
#include "SceneManager.h"

RenderContainer::RenderContainer()
{
	_renders.push_back(SceneManager::GetInstance());

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

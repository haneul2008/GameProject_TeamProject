#include "Core.h"
#include "UpdateContainer.h"
#include "RenderContainer.h"
#include "InitManager.h"

int main()
{
	UpdateContainer updateContainer;
	RenderContainer renderContainer;
	InitManager::GetInstance();

	Core::GetInstance()->Run();
}
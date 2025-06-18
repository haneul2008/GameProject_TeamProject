#include "Core.h"
#include "UpdateContainer.h"
#include "RenderContainer.h"
#include "InitManager.h"

int main()
{
	UpdateContainer updateContainer;
	RenderContainer renderContainer;

	InitManager inputManger;

	Core::GetInstance()->Run();
}
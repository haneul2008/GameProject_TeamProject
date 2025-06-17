#include "Core.h"
#include "UpdateContainer.h"
#include "RenderContainer.h"

int main()
{
	UpdateContainer updateContainer;
	RenderContainer renderContainer;
	Core::GetInstance()->Run();
}
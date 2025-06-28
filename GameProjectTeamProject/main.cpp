#include "Core.h"
#include "Console.h"
#include "UpdateContainer.h"
#include "RenderContainer.h"
#include "InitManager.h"
#include "Mci.h"

int main()
{
	SetConsoleFont(L"Consolas", { 18,18 }, 1);
	SetConsoleSetting(0, 0, true, L"Proto Rogue");
	SetCursorVisual(false, 1);

	InitAllSounds();

	UpdateContainer updateContainer;
	RenderContainer renderContainer;
	InitManager::GetInstance();

	Core::GetInstance()->Run();

	ReleaseAllSounds();
}
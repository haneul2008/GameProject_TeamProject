#include "Transition.h"
#include "Console.h"
#include "Mci.h"
#pragma comment(lib, "winmm")

Transition::Transition()
{
	PlaySoundID(SOUNDID::Transition);

	COORD resolution = GetConsoleResolution();
	int thickness = 7;
	for(int y = 0; y < resolution.Y; y += thickness)
	{
		for(int x = 0; x < resolution.X; ++x)
		{
			SetColor(COLOR::WHITE, COLOR::LIGHT_GRAY);
			for(int i = 0; i < thickness; ++i)
			{
				if (y + i >= resolution.Y) break;
				MoveCursor(x, y + i);
				std::cout << "  ";
			}
			FrameSync(1500);
		}
	}
	FrameSync(10);
	SetColor();
	system("cls");
}
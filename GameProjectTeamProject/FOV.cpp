#include "FOV.h"

void FOV::UpdateFov(const Pos& targetPos)
{
	if (_stage->curMap[targetPos.y][targetPos.x].isHide == false) return;

	for (const PROOM room : _rooms)
	{
		if (room->IsOverlap(targetPos))
		{
			for (int y = room->y; y < room->y + room->height; ++y)
			{
				for (int x = room->x; x < room->x + room->width; ++x)
					_stage->curMap[y][x].isHide = false;
			}

			return;
		}
	}

	_stage->curMap[targetPos.y][targetPos.x].isHide = false;
}

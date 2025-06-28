#include "FOV.h"

void FOV::UpdateFov(const Pos& targetPos)
{

	for (const PROOM room : _rooms)
	{
		if (room->isHide == false) return;

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

	Pos posArr[5] =
	{
		{targetPos.x, targetPos.y},
		{targetPos.x + 1, targetPos.y},
		{targetPos.x, targetPos.y + 1},
		{targetPos.x - 1, targetPos.y},
		{targetPos.x, targetPos.y - 1}
	};

	for (const Pos& pos : posArr)
	{
		if (_stage->curMap[pos.y][pos.x].tile == Tile::DOOR ||
			_stage->curMap[pos.y][pos.x].tile == Tile::ROAD)
		_stage->curMap[pos.y][pos.x].isHide = false;
	}
}

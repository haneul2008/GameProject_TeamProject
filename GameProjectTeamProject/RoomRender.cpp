#include "RoomRender.h"
#include "Enums.h"


void RoomRender::DrawRoom(const PSTAGE stage, const PROOM room) const
{
	int xLeft = room->x;
	int xRight = xLeft + room->width - 1;
	int yTop = room->y;
	int yBottom = yTop + room->height - 1;

	for (int y = yTop; y <= yBottom; ++y)
	{
		for (int x = xLeft; x <= xRight; ++x)
		{
			if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)
				continue;

			if (x == xLeft || x == xRight || y == yTop || y == yBottom)
				stage->curMap[y][x] = (char)Tile::WALL;
			else
				stage->curMap[y][x] = (char)Tile::ROAD;
		}
	}
}

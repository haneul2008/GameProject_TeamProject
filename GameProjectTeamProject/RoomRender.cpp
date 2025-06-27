#include "RoomRender.h"
#include "Enums.h"


RoomRender::RoomRender(const PSTAGE stage)
{
	for (int i = 0; i < MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < MAP_WIDTH; ++j)
		{
			stage->curMap[i][j].SetTile(Tile::EMPTY);
		}
	}
}

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
			if (x == xLeft || x == xRight || y == yTop || y == yBottom)
				stage->curMap[y][x].SetTile(Tile::WALL);
			else
				stage->curMap[y][x].SetTile(Tile::ROAD);
		}
	}

	Pos startPos = stage->startPos;
	Pos endPos = stage->endPos;

	stage->curMap[startPos.y][startPos.x].SetTile(Tile::START);
	stage->curMap[endPos.y][endPos.x].SetTile(Tile::GOAL);
}

void RoomRender::DrawPath(const PSTAGE stage, Path& pathList)
{
	for (int i = 0; i < pathList.size(); ++i)
	{
		Pos pos = std::move(pathList[i]);

		if (i == 0 || i == pathList.size() - 1)
			stage->curMap[pos.y][pos.x].SetTile(Tile::DOOR);
		else
			stage->curMap[pos.y][pos.x].SetTile(Tile::ROAD);
	}
}

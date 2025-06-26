#pragma once
#include<Windows.h>
#include"Constants.h"
#include"Object.h"
#include"Enums.h"

struct Rect
{
	int x, y;
	int width, height;

	Pos GetCenter() const {
		return {
			x + width / 2,
			y + height / 2
		};
	}

	const bool operator == (const Rect& other) const
	{
		return x == other.x && y == other.y
			&& width == other.width && height == other.height;
	}
};

typedef struct _room
{
	int x;
	int y;
	int width, height;

	Pos GetCenter() const {
		return {
			x + width / 2,
			y + height / 2
		};
	}

	bool IsOverlap(const Pos& other) const {
		bool isOverlapX = (x <= other.x) &&
			(other.x <= x + width);

		bool isOverlapY = (y <= other.y) &&
			(other.y <= y + height);

		return isOverlapX && isOverlapY;
	}
}ROOM, * PROOM;

typedef struct _stage
{
	char(*curMap)[MAP_WIDTH];
	COORD startPos;
	COORD endPos;
}STAGE, * PSTAGE;

typedef std::vector<Pos> Path;
typedef std::vector<Path> PathList;

struct RoomInfo
{
	std::vector<PROOM> rooms;
	PathList pathList;
};
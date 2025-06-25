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

	bool IsOverlap(const _room& other) const {
		bool noOverlapX = (x < other.x + other.width + ROOM_MINDISTANCE) &&
			(other.x < x + width + ROOM_MINDISTANCE);

		bool noOverlapY = (y < other.y + other.height + ROOM_MINDISTANCE) &&
			(other.y < y + height + ROOM_MINDISTANCE);

		return noOverlapX && noOverlapY;
	}
}ROOM, * PROOM;

typedef struct _stage
{
	char(*curMap)[MAP_WIDTH];
	COORD startPos;
	COORD endPos;
}STAGE, * PSTAGE;

struct Vector
{
	int x, y;
	Vector(int initX, int initY) :x(initX), y(initY) {};

	Dir GetDir()
	{
		Dir result = Dir::ZERO;

		if (x == 0 && y == 0) return result;

		if (std::abs(x) > std::abs(y))
		{
			if (x > 0)
				result = Dir::RIGHT;
			else
				result = Dir::LEFT;
		}
		else
		{
			if (y > 0)
				result = Dir::UP;
			else
				result = Dir::DOWN;
		}

		return result;
	}
};

struct RoomInfo
{
	std::vector<PROOM> rooms;
	std::vector<std::vector<Pos>> pathList;
};
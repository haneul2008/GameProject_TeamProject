#pragma once
#define NOMINMAX
#include<Windows.h>
#include"Constants.h"
#include"Object.h"

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

struct ConnectedRoomPair
{
	Pos room1;
	Pos room2;

	const bool operator ==(const ConnectedRoomPair& other) const
	{
		return (room1 == other.room1 || room2 == other.room2) &&
			(room2 == other.room1 || room2 == other.room2);
	}
};
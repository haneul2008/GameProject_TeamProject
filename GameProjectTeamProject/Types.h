#pragma once
#define NOMINMAX
#include<Windows.h>
#include"Constants.h"

struct Rect
{
	int x, y;
	int width, height;
};

typedef struct _room
{
	int x;
	int y;
	int width, height;

	COORD GetCenter() const {
		return {
			static_cast<SHORT>(x + width / 2),
			static_cast<SHORT>(y + height / 2)
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
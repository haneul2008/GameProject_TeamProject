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

struct RenderTile
{
	void SetTile(Tile initTile)
	{
		tile = initTile;

		if (initTile == Tile::WALL)
			symbol = "■"; // 벽
		else if (initTile == Tile::ROAD)
			symbol = "·"; // 길
		else if (initTile == Tile::START)
			symbol = "☆"; // 시작 포탈
		else if (initTile == Tile::GOAL)
			symbol = "▤"; // 목표 포탈
		else if (initTile == Tile::DOOR)
			symbol = "Π"; // 문
		else if (initTile == Tile::EMPTY)
			symbol = "  ";
	}

	Tile tile;
	std::string symbol;
	bool isHide;
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
			(other.x <= x + width - 1);

		bool isOverlapY = (y <= other.y) &&
			(other.y <= y + height - 1);

		return isOverlapX && isOverlapY;
	}
}ROOM, * PROOM;

typedef struct _stage
{
	RenderTile(*curMap)[MAP_WIDTH];
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
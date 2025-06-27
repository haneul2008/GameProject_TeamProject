#pragma once
#include<Windows.h>
#include<string>
#include "Console.h"
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
	RenderTile() : tile(),
		symbol(""),
		textColor(),
		isHide(true) {};

	void SetTile(Tile initTile)
	{
		tile = initTile;

		switch (initTile)
		{
		case Tile::WALL:
			symbol = "■"; // 벽
			textColor = COLOR::GRAY;
			break;
		case Tile::ROAD:
			symbol = "·"; // 길
			textColor = COLOR::GRAY;
			break;
		case Tile::START:
			symbol = "▣"; // 시작 포탈
			textColor = COLOR::LIGHT_YELLOW;
			break;
		case Tile::GOAL:
			symbol = "▤"; // 목표 포탈
			textColor = COLOR::GRAY;
			break;
		case Tile::DOOR:
			symbol = "Π"; // 문
			textColor = COLOR::LIGHT_RED;
			break;
		case Tile::EMPTY:
			symbol = "  ";
			textColor = COLOR::BLACK;
			break;
		default:
			break;
		}
	}

	Tile tile;
	COLOR textColor;
	std::string symbol;
	bool isHide;
};


typedef struct _room
{
	int x;
	int y;
	int width, height;
	bool isHide;

	_room() :
		x(0),
		y(0),
		width(0),
		height(0),
		isHide(true) {};

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
	std::vector<PROOM> rooms;
	Pos startPos;
	Pos endPos;
}STAGE, * PSTAGE;

typedef std::vector<Pos> Path;
typedef std::vector<Path> PathList;

struct RoomInfo
{
	std::vector<PROOM> rooms;
	PathList pathList;
};
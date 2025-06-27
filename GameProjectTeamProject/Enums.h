#pragma once

enum class Tile
{
	WALL = '0', ROAD, START, GOAL, DOOR, EMPTY
};

enum class WallSide
{
	TOP, BOTTOM, LEFT, RIGHT, END
};
#pragma once

enum class Tile
{
	WALL = '0', ROAD, START, GOAL, DOOR
};

enum class WallSide
{
	TOP, BOTTOM, LEFT, RIGHT, END
};

enum class Dir
{
	UP, DOWN, LEFT, RIGHT, ZERO
};
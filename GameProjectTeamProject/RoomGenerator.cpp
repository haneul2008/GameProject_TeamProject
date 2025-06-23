#include <random>
#include <algorithm>
#include "Enums.h"
#include "RoomGenerator.h"

void RoomGenerator::GenerateRooms(PSTAGE stage)
{
	_roomList.clear();
	Rect rootRegion = { 1, 1, MAP_WIDTH - 1, MAP_HEIGHT - 1 };
	auto rooms = SplitRegion(rootRegion, _maxDepth);
	_roomList = rooms;
	FillRoom(stage);
	ConnectRooms(stage, _roomList);
}

void RoomGenerator::FillRoom(PSTAGE stage)
{
	for (const Rect& room : _roomList)
	{
		for (int y = room.y; y < room.y + room.height; ++y)
		{
			for (int x = room.x; x < room.x + room.width; ++x)
			{
				bool isEdge = (y == room.y || y == room.y + room.height - 1 ||
					x == room.x || x == room.x + room.width - 1);

				stage->curMap[y][x] = isEdge ? (char)Tile::WALL : (char)Tile::ROAD; // 벽 or 바닥
			}
		}
	}
}

std::vector<Rect> RoomGenerator::SplitRegion(const Rect& region, int depth)
{
	std::vector<Rect> result;

	bool canDivideX = region.width >= MIN_ROOM_WIDTH * 2;
	bool canDivideY = region.height >= MIN_ROOM_HEIGHT * 2;

	bool canContinue = (depth > 0) && (canDivideX || canDivideY);

	if (!canContinue)
	{
		if (region.width >= MIN_ROOM_WIDTH + 2 &&
			region.height >= MIN_ROOM_HEIGHT + 2)
		{
			Rect room = CreateRoom(region);
			if (room.width > 0 && room.height > 0)
				result.push_back(room);
		}
		return result;
	}

	std::mt19937 rng(std::random_device{}());

	// 분할 방향 결정
	bool divideVertically;
	if (canDivideX && canDivideY)
		divideVertically = rng() % 2 == 0;
	else
		divideVertically = canDivideX;

	std::vector<Rect> leftRooms, rightRooms;

	if (divideVertically)
	{
		int splitX = region.x + region.width / 2;
		Rect left = { region.x, region.y, splitX - region.x, region.height };
		Rect right = { splitX, region.y, region.x + region.width - splitX, region.height };

		leftRooms = SplitRegion(left, depth - 1);
		rightRooms = SplitRegion(right, depth - 1);
	}
	else
	{
		int splitY = region.y + region.height / 2;
		Rect top = { region.x, region.y, region.width, splitY - region.y };
		Rect bottom = { region.x, splitY, region.width, region.y + region.height - splitY };

		leftRooms = SplitRegion(top, depth - 1);
		rightRooms = SplitRegion(bottom, depth - 1);
	}

	result.insert(result.end(), leftRooms.begin(), leftRooms.end());
	result.insert(result.end(), rightRooms.begin(), rightRooms.end());

	return result;
}

Rect RoomGenerator::CreateRoom(const Rect& region)
{
	std::mt19937 rng(std::random_device{}());

	int innerW = region.width - 2;
	int innerH = region.height - 2;

	if (innerW < MIN_ROOM_WIDTH || innerH < MIN_ROOM_HEIGHT)
		return {};

	std::uniform_int_distribution<int> rangew(MIN_ROOM_WIDTH, innerW);
	std::uniform_int_distribution<int> rangeh(MIN_ROOM_HEIGHT, innerH);

	int rw = rangew(rng);
	int rh = rangeh(rng);

	std::uniform_int_distribution<int> rangex(1, region.width - rw - 1);
	std::uniform_int_distribution<int> rangey(1, region.height - rh - 1);

	int rx = region.x + rangex(rng);
	int ry = region.y + rangey(rng);

	return { rx, ry, rw, rh };
}

void RoomGenerator::ConnectRooms(const PSTAGE stage, const std::vector<Rect>& rooms)
{

}

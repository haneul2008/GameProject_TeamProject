#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>
#include "Enums.h"
#include "RoomGenerator.h"

vector<PROOM> RoomGenerator::GenerateRooms(PSTAGE stage)
{
	_roomList.clear();
	Rect rootRegion = { 1, 1, MAP_WIDTH - 1, MAP_HEIGHT - 1 };
	SplitRegion(rootRegion, _maxDepth);
	ConnectRooms(stage, _roomList);
	return _roomList;
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
			PROOM room = CreateRoom(region);
			_roomList.push_back(room);

			if (room->width > 0 && room->height > 0)
				result.push_back({room->x, room->y, room->width, room->height});
		}
		return result;
	}

	std::mt19937 rng(std::random_device{}());

	bool divideVertical;
	if (canDivideX && canDivideY)
		divideVertical = rng() % 2 == 0;
	else
		divideVertical = canDivideX;

	std::vector<Rect> leftRooms, rightRooms;

	if (divideVertical)
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

PROOM RoomGenerator::CreateRoom(const Rect& region)
{
	std::mt19937 rng(std::random_device{}());

	int innerW = region.width - 2;
	int innerH = region.height - 2;

	if (innerW < MIN_ROOM_WIDTH || innerH < MIN_ROOM_HEIGHT)
		return nullptr;

	std::uniform_int_distribution<int> rangew(MIN_ROOM_WIDTH, MAX_ROOM_WIDTH);
	std::uniform_int_distribution<int> rangeh(MIN_ROOM_HEIGHT, MAX_ROOM_HEIGHT);

	int rw = rangew(rng);
	int rh = rangeh(rng);

	std::uniform_int_distribution<int> rangex(1, region.width - rw - 1);
	std::uniform_int_distribution<int> rangey(1, region.height - rh - 1);

	int rx = region.x + rangex(rng);
	int ry = region.y + rangey(rng);

	ROOM room;
	room.x = rx;
	room.y = ry;
	room.width = rw;
	room.height = rh;

	return &room;
}

void RoomGenerator::ConnectRooms(const PSTAGE stage, const std::vector<PROOM>& rooms)
{
	float distance;
	PROOM targetRoom = rooms[0];
	float shortnessDistance = 1000;
	std::vector<Pos> pathList;
	std::vector<ConnectedRoomPair> connectedRooms;

	for (const PROOM room : rooms)
	{
		pathList.clear();
		Pos center = room->GetCenter();

		for (const PROOM& otherRoom : rooms)
		{
			if (room == otherRoom) continue;

			distance = std::sqrt(std::pow(center.x, 2) + std::pow(center.y, 2));

			if (distance < shortnessDistance)
			{
				targetRoom = otherRoom;
				shortnessDistance = distance;
			}
		}

		ConnectedRoomPair roomPair = { center, targetRoom->GetCenter() };
		bool isContinue = false;

		for (ConnectedRoomPair pair : connectedRooms)
		{
			if (pair == roomPair)
			{
				isContinue = true;
				break;
			}
		}

		if (isContinue) continue;

		CalculatePath(stage, room, targetRoom);
		connectedRooms.push_back(roomPair);
	}
}

void RoomGenerator::CalculatePath(const PSTAGE stage, const PROOM room, const PROOM targetRoom)
{
	/*vector<Pos> pathList;

	Pos current = GetRandomWallPos(room);
	Pos target = GetRandomWallPos(targetRoom);

	int distanceX = std::abs(target.x - current.x);
	int distanceY = std::abs(target.y - current.y);


	if (distanceX > distanceY)
	{
		bool isOverWidth = distanceX > room->width / 2;

		if (isOverWidth)
		{
		}
		else
			GetPath(pathList, current, target);
	}
	else
	{
		bool isOverHeight = distanceY > room->height / 2;

		if (isOverHeight)
		{

		}
		else
			GetPath(pathList, current, target);
	}

	for (int i = 0; i < pathList.size(); ++i)
	{
		Pos pos = std::move(pathList[i]);

		if (i == 0 || i == pathList.size() - 1)
			stage->curMap[pos.y][pos.x] = (char)Tile::DOOR;
		else
			stage->curMap[pos.y][pos.x] = (char)Tile::ROAD;
	}*/
}

void RoomGenerator::GetPath(vector<Pos>& pathList, const Pos& start, const Pos& end)
{
	bool isHorizontal = end.y == start.y;
	bool isVertical = end.x == start.x;

	if (isHorizontal)
	{
		int distance = std::abs(end.x - start.x);
		int dir = (end.x - start.x) / distance;

		for (int i = 0; i <= distance; ++i)
			pathList.push_back({ start.x + dir * i, start.y });
	}
	else if (isVertical)
	{
		int distance = std::abs(end.y - start.y);
		int dir = (end.y - start.y) / distance;

		for (int i = 0; i <= distance; ++i)
			pathList.push_back({ start.x, start.y + dir });
	}
}

int RoomGenerator::GetRandomPoint(int start, int end)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> range(start, end);
	return range(rng);
}

Pos RoomGenerator::GetRandomWallPos(const PROOM room, int side)
{
	Pos result;

	switch (side)
	{
	case 0:
		result = { GetRandomPoint(room->x + 2, room->x + room->width - 2), room->y };
		break;
	case 1:
		result = { GetRandomPoint(room->x + 2, room->x + room->width - 2), room->y + room->height - 1 };
		break;
	case 2:
		result = { room->x, GetRandomPoint(room->y + 2, room->y + room->height - 2) };
		break;
	case 3:
		result = { room->x + room->width - 2, GetRandomPoint(room->y + 1, room->y + room->height - 2) };
		break;
	}

	return result;
}


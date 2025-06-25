#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>
#include "RoomGenerator.h"

RoomInfo RoomGenerator::GenerateRooms(PSTAGE stage)
{
	_roomList.clear();
	Rect rootRegion = { 1, 1, MAP_WIDTH - 1, MAP_HEIGHT - 1 };
	SplitRegion(rootRegion, _maxDepth);
	vector<vector<Pos>> pathList = ConnectRooms(stage, _roomList);
	return { _roomList, pathList };
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
				result.push_back({ room->x, room->y, room->width, room->height });
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

	PROOM room = new ROOM;
	room->x = rx;
	room->y = ry;
	room->width = rw;
	room->height = rh;

	return room;
}

vector<vector<Pos>> RoomGenerator::ConnectRooms(const PSTAGE stage, const std::vector<PROOM>& rooms)
{
	vector<vector<Pos>> allPath;

	float distance;
	PROOM targetRoom = rooms[0];
	float shortnessDistance = 1000;

	std::unordered_map<PROOM, vector<PROOM>> connectedRoomPairs;

	for (const PROOM room : rooms)
	{
		Pos center = room->GetCenter();
		shortnessDistance = 1000;

		for (const PROOM& otherRoom : rooms)
		{
			if (room == otherRoom) continue;

			Pos otherCenter = otherRoom->GetCenter();
			distance = std::abs(otherRoom->x - room->x) + std::abs(otherRoom->y - room->y);

			if (distance < shortnessDistance)
			{
				targetRoom = otherRoom;
				shortnessDistance = distance;
			}
		}

		vector<PROOM>* links = &connectedRoomPairs[room];

		if (std::find(links->begin(), links->end(), targetRoom) != links->end()) continue;

		connectedRoomPairs[room].push_back(targetRoom);
		connectedRoomPairs[targetRoom].push_back(room);
		allPath.push_back(CalculatePath(stage, room, targetRoom));
	}

	ConnectAllRoom(stage, rooms, connectedRoomPairs);
	return allPath;
}

vector<Pos> RoomGenerator::CalculatePath(const PSTAGE stage, const PROOM room, const PROOM targetRoom)
{
	vector<Pos> pathList;
	std::pair<WallSide, WallSide> sidePair = GetWallSide(room, targetRoom);

	Pos current = GetRandomWallPos(room, sidePair.first);
	Pos target = GetRandomWallPos(targetRoom, sidePair.second);

	if (current.x == target.x || current.y == target.y)
		GetPath(pathList, current, target);
	else
	{
		Pos middlePoints[2] = {};
		int deltaY = (target.y + current.y) / 2;
		int deltaX = (target.x + current.x) / 2;

		Vector dir = { target.x - current.x, target.y - current.y };
		switch (dir.GetDir())
		{
		case Dir::UP:
		case Dir::DOWN:
			middlePoints[0] = { current.x, deltaY };
			middlePoints[1] = { target.x, deltaY };
			break;
		case Dir::LEFT:
		case Dir::RIGHT:
			middlePoints[0] = { deltaX, current.y };
			middlePoints[1] = { deltaX, target.y };
			break;
		default:
			break;
		}

		GetPath(pathList, current, middlePoints[0]);
		GetPath(pathList, middlePoints[0], middlePoints[1]);
		GetPath(pathList, middlePoints[1], target);
	}

	return pathList;
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
			pathList.push_back({ start.x, start.y + dir * i });
	}
}

int RoomGenerator::GetRandomPoint(int start, int end)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> range(start, end);
	return range(rng);
}

std::pair<WallSide, WallSide> RoomGenerator::GetWallSide(const PROOM start, const PROOM end)
{
	std::pair<WallSide, WallSide> result;

	int maxDistance = 1000;

	Pos startWallPos;
	Pos endWallPos;

	for (int i = 0; i < (int)WallSide::END; ++i)
	{
		startWallPos = GetWallCenterPos(start, (WallSide)i);

		for (int j = 0; j < (int)WallSide::END; ++j)
		{
			if (i == j) continue;

			endWallPos = GetWallCenterPos(end, (WallSide)j);
			int distance = std::abs(end->x - start->x) + std::abs(end->y - start->y);

			if (distance < maxDistance)
			{
				result = { (WallSide)i, (WallSide)j };
				maxDistance = distance;
			}
		}
	}

	return result;
}

Pos RoomGenerator::GetRandomWallPos(const PROOM room, WallSide side)
{
	Pos result;

	switch (side)
	{
	case WallSide::TOP:
		result = { GetRandomPoint(room->x + 1, room->x + room->width - 2), room->y };
		break;
	case WallSide::BOTTOM:
		result = { GetRandomPoint(room->x + 1, room->x + room->width - 2), room->y + room->height - 1 };
		break;
	case WallSide::LEFT:
		result = { room->x, GetRandomPoint(room->y + 2, room->y + room->height - 3) };
		break;
	case WallSide::RIGHT:
		result = { room->x + room->width - 1, GetRandomPoint(room->y + 2, room->y + room->height - 3) };
		break;
	default:
		result = {};
	}

	return result;
}

Pos RoomGenerator::GetWallCenterPos(const PROOM room, WallSide side)
{
	Pos result;

	switch (side)
	{
	case WallSide::TOP:
		result = { room->x + room->width / 2, room->y };
		break;
	case WallSide::BOTTOM:
		result = { room->x + room->width / 2, room->y + room->height - 1 };
		break;
	case WallSide::LEFT:
		result = { room->x, room->y + room->height / 2 };
		break;
	case WallSide::RIGHT:
		result = { room->x + room->width - 1, room->y + room->height / 2 };
		break;
	default:
		result = {};
		break;
	}

	return result;
}

void RoomGenerator::ConnectAllRoom(const PSTAGE stage, const vector<PROOM>& rooms, std::unordered_map<PROOM, vector<PROOM>>& connectedRoomPairs)
{
	std::unordered_map<PROOM, bool> visitPairs;
	std::vector<std::vector<PROOM>> connectedRooms;

	for (const PROOM& room : rooms)
	{
		if (visitPairs[room]) continue;

		std::vector<PROOM> stack = { room };
		std::vector<PROOM> component;

		while (!stack.empty())
		{
			PROOM currentRoom = stack.back();
			stack.pop_back();

			if (visitPairs[currentRoom]) continue;

			visitPairs[currentRoom] = true;
			component.push_back(currentRoom);

			for (PROOM room : connectedRoomPairs[currentRoom])
			{
				if (!visitPairs[room])
					stack.push_back(room);
			}
		}
		connectedRooms.push_back(component);
	}

	if (connectedRooms.size() <= 1) return;

	for (int i = 0; i < connectedRooms.size() - 1; ++i)
	{
		float maxDistance = 1000;
		PROOM start = nullptr;
		PROOM end = nullptr;

		for (PROOM room : connectedRooms[i])
		{
			for (PROOM other : connectedRooms[i + 1])
			{
				float distance = std::abs(room->x - other->x) + std::abs(room->y - other->y);
				if (distance < maxDistance)
				{
					maxDistance = distance;
					start = room;
					end = other;
				}
			}
		}

		if (start && end)
		{
			connectedRoomPairs[start].push_back(end);
			connectedRoomPairs[end].push_back(start);
			CalculatePath(stage, start, end);
		}
	}
}

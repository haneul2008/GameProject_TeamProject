#pragma once
#include <vector>
#include "Types.h"
#include "Constants.h"

class RoomGenerator
{
public:
	RoomGenerator(int maxDepth) : _maxDepth(maxDepth) {}
public:
	void GenerateRooms(PSTAGE stage);
private:
	void FillRoom(PSTAGE stage);
	std::vector<Rect> SplitRegion(const Rect& region, int depth);
	Rect CreateRoom(const Rect& region);
	void ConnectRooms(const PSTAGE stage, const std::vector<Rect>& rooms);
private:
	int _maxDepth;
	std::vector<Rect> _roomList;
};

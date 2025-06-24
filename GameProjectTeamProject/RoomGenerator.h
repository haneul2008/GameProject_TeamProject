#pragma once
#include <vector>
#include "Types.h"
#include "Constants.h"

using std::vector;

class RoomGenerator
{
public:
	RoomGenerator(int maxDepth) : _maxDepth(maxDepth) {}
public:
	vector<PROOM> GenerateRooms(PSTAGE stage);
private:
	vector<Rect> SplitRegion(const Rect& region, int depth);
	PROOM CreateRoom(const Rect& region);
	void ConnectRooms(const PSTAGE stage, const std::vector<PROOM>& rooms);
	void CalculatePath(const PSTAGE stage, const PROOM room, const PROOM targetRoom);
	void GetPath(vector<Pos>& pathList, const Pos& start, const Pos& end);
	int GetRandomPoint(int start, int end);
	Pos GetRandomWallPos(const PROOM room, int side);
private:
	int _maxDepth;
	vector<PROOM> _roomList;
};

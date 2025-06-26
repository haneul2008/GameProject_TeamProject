#pragma once
#include <vector>
#include <unordered_map>
#include "Types.h"
#include "Enums.h"
#include "Constants.h"

using std::vector;

class RoomGenerator
{
public:
	RoomGenerator(int maxDepth) : _maxDepth(maxDepth) {}
public:
	RoomInfo GenerateRooms(PSTAGE stage);
private:
	vector<Rect> SplitRegion(const Rect& region, int depth);
	PROOM CreateRoom(const Rect& region);
	PathList ConnectRooms(const PSTAGE stage, const std::vector<PROOM>& rooms);
	Path CalculatePath(const PSTAGE stage, const PROOM room, const PROOM targetRoom);
	Path GetOptimalPath(const WallSide& currentSide, const WallSide& targetSide,
		const Pos& current, const Pos& target);
	void SetStraightPath(vector<Pos>& pathList, const Pos& start, const Pos& end);
	int GetRandomPoint(int start, int end);
	std::pair<WallSide, WallSide> GetWallSide(const PROOM start, const PROOM end);
	Pos GetRandomWallPos(const PROOM room, WallSide side);
	Pos GetWallCenterPos(const PROOM room, WallSide side);
	PathList ConnectAllRoom(const PSTAGE stage, const vector<PROOM>& rooms, 
		std::unordered_map<PROOM, vector<PROOM>>& connectedRoomPairs);
private:
	int _maxDepth;
	vector<PROOM> _roomList;
};

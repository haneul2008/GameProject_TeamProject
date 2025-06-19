#include<math.h>
#include "PathGenerator.h"
#include "Enums.h"

PathGenerator::PathGenerator(const vector<PROOM>& rooms, PSTAGE stage)
{
	for (PROOM room : rooms)
	{
		PROOM nearestRoom = GetNearestRoom(rooms, room);
		PATH path = CalculatePath(room, nearestRoom);

		for (Pos pos : path)
			stage->curMap[pos.y][pos.x] = (char)Tile::ROAD;
	}
}

PROOM PathGenerator::GetNearestRoom(const vector<PROOM>& rooms, PROOM room)
{
	PROOM result = nullptr;
	float shortnessDistnace = 1000;

	for (PROOM otherRoom : rooms)
	{
		if (otherRoom == room) continue;

		int xDistance = otherRoom->GetCenter().X - room->GetCenter().X;
		int yDistance = otherRoom->GetCenter().Y - room->GetCenter().Y;
		float distance = sqrt(pow(xDistance, 2) + pow(yDistance, 2));
		
		if (distance < shortnessDistnace)
		{
			result = otherRoom;
			shortnessDistnace = distance;
		}
	}

	return result;
}

PATH PathGenerator::CalculatePath(PROOM startRoom, PROOM endRoom)
{
	PATH path;

	int xDistance = abs(endRoom->GetCenter().X - startRoom->GetCenter().X);
	int yDistance = abs(endRoom->GetCenter().Y - startRoom->GetCenter().Y);
	
	//복도가 가로인지 세로인지
	bool isHorizontal = xDistance > yDistance;

	//isIncreasePath가 true라면 증가하는 방향으로 감
	//true : isHorizontal아 true일때 오른쪽으로 복도를 만듦
	bool isIncreasePath = false;
	
	if (isHorizontal)
		isIncreasePath = endRoom->GetCenter().X > startRoom->GetCenter().X;
	else
		isIncreasePath = endRoom->GetCenter().Y > startRoom->GetCenter().Y;

	while (true)
	{

	}

	return path;
}

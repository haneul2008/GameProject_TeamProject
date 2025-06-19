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
	
	//������ �������� ��������
	bool isHorizontal = xDistance > yDistance;

	//isIncreasePath�� true��� �����ϴ� �������� ��
	//true : isHorizontal�� true�϶� ���������� ������ ����
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

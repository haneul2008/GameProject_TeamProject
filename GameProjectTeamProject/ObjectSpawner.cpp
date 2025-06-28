#include<random>
#include "ObjectSpawner.h"

ObjectSpawner::ObjectSpawner(PSTAGE stage) : _stage(nullptr), _spawnPosPairs()
{
	_stage = stage;
}

void ObjectSpawner::Spawn(Object* object)
{
	PROOM targetRoom = _stage->rooms[0];
	int maxSize = 1000;

	for(const auto& pair : _spawnPosPairs)
	{
		if (pair.second.size() < maxSize)
		{
			maxSize = pair.second.size();
			targetRoom = pair.first;
			break;
		}
	}

	int randX = GetRandomPoint(targetRoom->x + 1, targetRoom->x + targetRoom->width - 2);
	int randY = GetRandomPoint(targetRoom->y + 1, targetRoom->y + targetRoom->height - 2);

}

int ObjectSpawner::GetRandomPoint(int start, int end)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> range(start, end);
	return range(rng);
}

#include "ObjectSpawner.h"
#include "EntityManager.h"
#include "Random.h"

ObjectSpawner::ObjectSpawner(PSTAGE stage) : _stage(nullptr), _spawnPosPairs()
{
	_stage = stage;
}

void ObjectSpawner::SetUp()
{
	_spawnPosPairs.clear();

	for (const PROOM room : _stage->rooms)
	{
		_spawnPosPairs[room] = vector<Pos>();
	}
}

Object* ObjectSpawner::Spawn(std::string poolName)
{
	PROOM targetRoom = _stage->rooms[0];
	int minSize = 1000;

	for(const auto& pair : _spawnPosPairs)
	{
		if (pair.second.size() < minSize)
		{
			minSize = pair.second.size();
			targetRoom = pair.first;
		}
	}

	Random random;

	int randX = random.GetRandomPoint(targetRoom->x + 1, targetRoom->x + targetRoom->width - 2);
	int randY = random.GetRandomPoint(targetRoom->y + 1, targetRoom->y + targetRoom->height - 2);

	Pos pos = { randX, randY };

	vector<Pos>& spawnPositions = _spawnPosPairs[targetRoom];
	if(std::find(spawnPositions.begin(), spawnPositions.end(), pos) != spawnPositions.end())
		return nullptr;

	_spawnPosPairs[targetRoom].push_back(pos);

	Object* newObj = EntityManager::GetInstance()->activeRandomObject(poolName);
	newObj->setPosition(pos);
	return newObj;
}

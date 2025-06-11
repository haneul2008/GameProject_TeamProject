#include "Physics.h"

PhysicsManager::PhysicsManager(int maxHieght, int maxWidth)
    :_maxHeight(maxHieght),
    _maxWidth(maxWidth)
{
    for (int y = 0; y < _maxHeight; ++y)
    {
        _physicsMap[y] = new ICollider * [_maxWidth];
        for (int x = 0; x < _maxWidth; ++x)
            _physicsMap[y][x] = nullptr;
    }
}

PhysicsManager::~PhysicsManager()
{
    for (int y = 0; y < _maxHeight; ++y)
    {
        delete[] _physicsMap[y];
    }
    delete[] _physicsMap;
}

const ICollider* PhysicsManager::getCollider(int x, int y)
{
    if (y < 0 || y >= _maxHeight || x < 0 || x >= _maxWidth)
        return nullptr;

    return _physicsMap[y][x];
}

const ICollider* PhysicsManager::getCollider(const Pos& pos)
{
    return this->getCollider(pos.x, pos.y);
}

void PhysicsManager::setCollider(ICollider* collider, int x, int y)
{
    if (y < 0 || y >= _maxHeight || x < 0 || x >= _maxHeight)
        return;

    _physicsMap[y][x] = collider;
}

void PhysicsManager::setCollider(ICollider* collider, const Pos & pos)
{
    return this->setCollider(collider, pos.x, pos.y);
}

const bool ICollider::getIsTrigger()
{
    return _isTrigger;
}

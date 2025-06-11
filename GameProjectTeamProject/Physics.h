#pragma once

#include "Object.h"

class ICollider
{
public:
    virtual bool collision() = 0;
    virtual const bool getIsTrigger();

protected:
    bool _isTrigger;
};

// singleton���� �ʿ䰡 ��������?
class PhysicsManager
{
public:
    PhysicsManager(int maxHieght, int maxWidth);
    ~PhysicsManager();

public:
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

public:
    const ICollider* getCollider(int x, int y);
    const ICollider* getCollider(const Pos& pos);

    void setCollider(ICollider* collider, int x, int y);
    void setCollider(ICollider* collider, const Pos& pos);

private:
    // ICollider*�� 2���� �迭
    ICollider*** _physicsMap;
    int _maxHeight;
    int _maxWidth;
};
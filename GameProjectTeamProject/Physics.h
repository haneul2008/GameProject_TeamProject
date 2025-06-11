#pragma once

#include "Object.h"
#include "Singletone.h"

class Collider
{
public:
    virtual bool calculateCollision(const Collider& other) const = 0;
    virtual bool isAnyTrigger(const Collider& other) const;
    virtual bool isOverlapLayer(int layer) const;

    virtual bool getIsTrigger() const;

    virtual int getLayer() const;
    virtual void setLayer(int layer);

protected:
    bool _isTrigger;
    int _layer;
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
    const Collider* getCollider(int x, int y);
    const Collider* getCollider(const Pos& pos);

    void setCollider(Collider* collider, int x, int y);
    void setCollider(Collider* collider, const Pos& pos);

private:
    // Collider*�� 2���� �迭
    Collider*** _physicsMap;
    int _maxHeight;
    int _maxWidth;
};
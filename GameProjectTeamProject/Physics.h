#pragma once

#include<vector>

#include "Object.h"
#include "Singletone.h"

class Collider
{
public:
    Collider();
    virtual ~Collider();

public:
    virtual void init(pPos pPos, bool trigger, int layer);
    virtual void active();
    virtual void deActive();

    virtual int getCollidedObjectLayer(const Collider& other);

    virtual bool isAnyTrigger(const Collider& other) const;
    virtual bool isOverlapLayer(int layer) const;

    virtual bool getIsTrigger() const;

    virtual int getLayer() const;
    virtual void setLayer(int layer);

    virtual pPos getPosition() const;
    virtual void setOriginPosition(pPos position);

    virtual bool calculateCollision(const Collider& other) const abstract;

protected:
    virtual bool tryCollision(const Pos& previousPos, const Pos& pos);

    virtual void onTriggerEvent(Collider& other, const Pos& previousPos) abstract;
    virtual void onCollisionEvent(Collider& other, const Pos& previousPos) abstract;

protected:
    pPos _pPosition;
    bool _isTrigger;
    int _layer;
};

// collider가 physics manager를 알고 그게 collider를 아는 기괴한 구조인데 어쩔 수 없다.
class PhysicsManager : public Singleton<PhysicsManager>
{
public:
    PhysicsManager();
    ~PhysicsManager() override;

public:
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

public:
    void setMaxMoveBound(int x, int y);

    Collider* getCollider(const Pos& pos) const;
    Collider* getCollider(const Collider& owner, int x, int y) const;
    Collider* getCollider(const Collider& owner, const Pos& pos) const;

    void addCollider(Collider* collider);
    void removeCollider(Collider* collider);

    int getMaxHeight();
    int getMaxWidth();

private:
    std::vector<Collider*> _colliders;
    int _maxHeight;
    int _maxWidth;
};
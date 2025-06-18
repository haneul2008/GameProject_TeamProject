#pragma once

#include "Object.h"
#include "Singletone.h"

class Collider
{
public:
    Collider();
    ~Collider();

public:
    virtual void init(pPos pPos, bool trigger, int layer);

    virtual int getCollidedObjectLayer(const Collider& other);

    virtual bool isAnyTrigger(const Collider& other) const;
    virtual bool isOverlapLayer(int layer) const;

    virtual bool getIsTrigger() const;

    virtual int getLayer() const;
    virtual void setLayer(int layer);

    virtual pPos getPosition() const;
    virtual void setPosition(pPos position);

protected:
    virtual bool calculateCollision(const Collider& other) const = 0;
    virtual bool tryCollision(const Pos& pos);

    virtual void onTriggerEvent(const Collider& other, const Pos& beforePosition) = 0;
    virtual void onCollisionEvent(const Collider& other, const Pos& beforePosition) = 0;

protected:
    pPos _position;
    bool _isTrigger;
    int _layer;
};

// collider�� physics manager�� �˰� �װ� collider�� �ƴ� �Ⱬ�� �����ε� ��¿ �� ����.
class PhysicsManager : public Singleton<PhysicsManager>
{
public:
    PhysicsManager();
    ~PhysicsManager() override;

public:
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;

public:
    void initialize(int maxHieght, int maxWidth);

    const Collider* getCollider(int x, int y) const;
    const Collider* getCollider(const Pos& pos) const;

    void setCollider(Collider* collider, int x, int y);
    void setCollider(Collider* collider, const Pos& pos);

    int getMaxHeight();
    int getMaxWidth();

private:
    // Collider*�� 2���� �迭
    // ���������� ��Ī�Ǵ� �ݶ��̴� ��
    Collider*** _physicsMap;
    int _maxHeight;
    int _maxWidth;
};
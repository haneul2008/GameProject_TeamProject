#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
public:
    // Collider��(��) ���� ��ӵ�
    bool calculateCollision(const Collider& other) const override;

    // Collider��(��) ���� ��ӵ�
    virtual void onTriggerEvent(Collider& other, const Pos& beforePosition) override abstract;
    virtual void onCollisionEvent(Collider& other, const Pos& beforePosition) override abstract;
};


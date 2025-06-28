#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
public:
    virtual ~PositionCollider() override;

public:
    // Collider��(��) ���� ��ӵ�
    bool calculateCollision(const Collider& other) const override;

    // Collider��(��) ���� ��ӵ�
    virtual void onTriggerEvent(Collider& other, const Pos& beforePosition) override;
    virtual void onCollisionEvent(Collider& other, const Pos& beforePosition) override;
};


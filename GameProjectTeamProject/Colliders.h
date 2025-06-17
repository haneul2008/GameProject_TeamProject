#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
public:
    // Collider��(��) ���� ��ӵ�
    bool calculateCollision(const Collider& other) const override;

    // Collider��(��) ���� ��ӵ�
    void onTriggerEvent(const Collider& other, const Pos& beforePosition) override = 0;
    void onCollisionEvent(const Collider& other, const Pos& beforePosition) override = 0;
};


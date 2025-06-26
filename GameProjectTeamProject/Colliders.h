#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
public:
    // Collider을(를) 통해 상속됨
    bool calculateCollision(const Collider& other) const override;

    // Collider을(를) 통해 상속됨
    virtual void onTriggerEvent(Collider& other, const Pos& beforePosition) override abstract;
    virtual void onCollisionEvent(Collider& other, const Pos& beforePosition) override abstract;
};


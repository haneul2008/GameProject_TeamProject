#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
    // Collider을(를) 통해 상속됨
    bool calculateCollision(const Collider& other) const override;
};


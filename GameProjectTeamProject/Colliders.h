#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
    // Collider��(��) ���� ��ӵ�
    bool calculateCollision(const Collider& other) const override;
};


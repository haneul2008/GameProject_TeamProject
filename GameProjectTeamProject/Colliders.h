#pragma once

#include "Physics.h"

class PositionCollider : virtual public Collider
{
public:
    // Collider��(��) ���� ��ӵ�
    bool calculateCollision(const Collider& other) const override;
};


#pragma once

#include "Object.h"
#include "Colliders.h"
#include "IUpdate.h"

class Entity : public virtual IUpdate, public virtual Object, public virtual PositionCollider
{
public:
    virtual ~Entity() override;

public:
    void Move(int x, int y);
    void Move(const Pos& pos);
    void MoveX(int value);
    void MoveY(int value);

    // IUpdate을(를) 통해 상속됨
    void Update() override;
    int GetPriotity() override;
    
protected:
    // PositionCollider을(를) 통해 상속됨
    // 상자 밀기 등은 필히 PhysicsManager에서 물리 맵 건들여야함.
    void onTriggerEvent(const Collider& other, const Pos& beforePosition) override;
    void onCollisionEvent(const Collider& other, const Pos& beforePosition) override;

private:
    int _tempMoveX;
    int _tempMoveY;
};


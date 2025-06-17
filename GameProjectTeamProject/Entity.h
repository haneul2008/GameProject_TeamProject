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

    // IUpdate��(��) ���� ��ӵ�
    void Update() override;
    int GetPriotity() override;
    
protected:
    // PositionCollider��(��) ���� ��ӵ�
    // ���� �б� ���� ���� PhysicsManager���� ���� �� �ǵ鿩����.
    void onTriggerEvent(const Collider& other, const Pos& beforePosition) override;
    void onCollisionEvent(const Collider& other, const Pos& beforePosition) override;

private:
    int _tempMoveX;
    int _tempMoveY;
};


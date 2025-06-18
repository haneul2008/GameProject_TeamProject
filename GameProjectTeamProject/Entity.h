#pragma once

#include "Object.h"
#include "Colliders.h"
#include "IUpdate.h"

class Entity : public virtual IUpdate, public virtual Object, public virtual PositionCollider
{
public:
    Entity();
    virtual ~Entity() override;

public:
    virtual void init(wchar_t defaultImage, bool trigger, int layer);

    void setPosition(const Pos& pos);

    void move(int x, int y);
    void move(const Pos& pos);
    void moveX(int value);
    void moveY(int value);

    // IUpdate을(를) 통해 상속됨
    void Update() override;
    int GetUpdatePriotity() override;
    // 일관성을 위해 대문자로 시작.
    void SetUpdatePriotity(int priority);
    
protected:
    // PositionCollider을(를) 통해 상속됨
    // 상자 밀기 등은 필히 PhysicsManager에서 물리 맵 건들여야함.
    void onTriggerEvent(const Collider& other, const Pos& newPosition) override;
    void onCollisionEvent(const Collider& other, const Pos& newPosition) override;

private:
    int _tempMoveX;
    int _tempMoveY;
    int _updatePriority;
};


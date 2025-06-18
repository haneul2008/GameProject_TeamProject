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

    // IUpdate��(��) ���� ��ӵ�
    void Update() override;
    int GetUpdatePriotity() override;
    // �ϰ����� ���� �빮�ڷ� ����.
    void SetUpdatePriotity(int priority);
    
protected:
    // PositionCollider��(��) ���� ��ӵ�
    // ���� �б� ���� ���� PhysicsManager���� ���� �� �ǵ鿩����.
    void onTriggerEvent(const Collider& other, const Pos& newPosition) override;
    void onCollisionEvent(const Collider& other, const Pos& newPosition) override;

private:
    int _tempMoveX;
    int _tempMoveY;
    int _updatePriority;
};


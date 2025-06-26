#pragma once

#include <string>

#include "Object.h"
#include "Colliders.h"
#include "IUpdate.h"
#include "IDamageable.h"

struct EntityStat
{
    int damage;
    int maxHp;
    int hp;
    int avoidance; // ȸ����
    int addDamagePer; // �ߵ� �ۼ�Ʈ

    static EntityStat makeStat(int damage, int maxHp, int avoidance, int addDamagePer);
};

class Entity : public virtual IUpdate, public virtual Object, public virtual PositionCollider, public virtual IDamageable
{
public:
    Entity();
    virtual ~Entity() override;
    Entity(Entity&& other);
    Entity(const Entity& other);

public:
    virtual void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer);
    virtual void active() override;

    void setPosition(const Pos& pos);

    void move(int x, int y);
    void move(const Pos& pos);
    void moveX(int value);
    void moveY(int value);

    virtual void applyMove();
    const EntityStat getStat() const;

    // IUpdate��(��) ���� ��ӵ�
    virtual void Update() override;
    int GetUpdatePriotity() override;
    // �ϰ����� ���� �빮�ڷ� ����.
    void SetUpdatePriotity(int priority);

    // IDamageable��(��) ���� ��ӵ�
    virtual void takeDamage(Entity* dealer, int damage) override;
    virtual void onHitEvent(Entity* dealer, int damage);
    virtual void onDeadEvent(Entity* dealer, int damage);

    void setName(std::string name = "NULL");
    std::string getName();
    
protected:
    // PositionCollider��(��) ���� ��ӵ�
    // ���� �б� ���� ���� PhysicsManager���� ���� �� �ǵ鿩����.
    virtual void onTriggerEvent(Collider& other, const Pos& newPosition) override;
    virtual void onCollisionEvent(Collider& other, const Pos& newPosition) override;

protected:
    EntityStat _entityStat;

protected:
    std::string _name;
    int _tempMoveX;
    int _tempMoveY;
    int _updatePriority;
};


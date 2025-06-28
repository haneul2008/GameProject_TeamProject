#pragma once

#include <string>
#include <queue>
#include <unordered_set>

#include "Object.h"
#include "Colliders.h"
#include "IUpdate.h"
#include "IDamageable.h"
#include "IDeadHandler.h"

struct EntityStat
{
    int damage;
    int maxHp;
    int hp;
    int avoidance; // 회피율
    int addDamagePer; // 추뎀 퍼센트

    EntityStat operator+(const EntityStat& other) const;

    static EntityStat makeStat(int damage, int maxHp, int avoidance, int addDamagePer, int hp = -1);
};

class Entity : public virtual IUpdate, public virtual Object, public virtual PositionCollider, public virtual IDamageable
{
public:
    Entity();
    virtual ~Entity() override;
    Entity(Entity&& other);
    Entity(const Entity& other);
    virtual Entity* newClone() override;

public:
    virtual void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer);
    virtual void active() override;
    virtual void deActive() override;

    void move(int x, int y);
    void move(const Pos& pos);
    void moveX(int value);
    void moveY(int value);

    virtual void applyMove();
    const EntityStat getStat() const;

    // IUpdate을(를) 통해 상속됨
    virtual void Update() override;
    int GetUpdatePriotity() override;
    // 일관성을 위해 대문자로 시작.
    void SetUpdatePriotity(int priority);

    // IDamageable을(를) 통해 상속됨
    virtual void takeDamage(Entity* dealer, int damage) override;
    virtual void onHitEvent(Entity* dealer, int damage);
    virtual void onDeadEvent(Entity* dealer, int damage);

    void addDeadListener(IDeadHandler* deadListener);
    void removeDeadListener(IDeadHandler* deadListener);

    void setName(std::string name = "NULL");
    std::string getName();
    
    void addAttackComment(const std::string& comment);
    virtual void attack(Entity* target, int damage);

    bool getIsdead() const;

protected:
    // PositionCollider을(를) 통해 상속됨
    virtual void onTriggerEvent(Collider& other, const Pos& newPosition) override;
    virtual void onCollisionEvent(Collider& other, const Pos& newPosition) override;

    std::string getAttackComment() const;

public:
    EntityStat stat;

protected:
    std::unordered_set<IDeadHandler*> _deadListeners;
    std::queue<IDeadHandler*> _removeToListeners;
    std::vector<std::string> _attckComments;

protected:
    std::string _name;
    int _tempMoveX;
    int _tempMoveY;
    int _updatePriority;
    bool _isDead;
};


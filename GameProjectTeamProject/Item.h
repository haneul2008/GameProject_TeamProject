#pragma once

#include "Object.h"
#include "Entity.h"
#include "Colliders.h"

class Item : public virtual Object, public virtual PositionCollider
{
public:
    virtual void init(wchar_t defaultImage, bool trigger, int layer);
    virtual void active() override;
    virtual void deActive() override;

    void setPosition(const Pos& pos);

    void setName(std::string name = "NULL");
    std::string getName() const;

    virtual void useItem(Entity* itemUser) abstract;

public:
    // PositionCollider을(를) 통해 상속됨
    void onTriggerEvent(Collider& other, const Pos& beforePosition) override;
    void onCollisionEvent(Collider& other, const Pos& beforePosition) override;

private:
    std::string _name;
};

class StatItem : public virtual Item
{
public:
    void setUpStat(const EntityStat& stat);

    // Item을(를) 통해 상속됨
    void useItem(Entity* itemUser) override;

private:
    EntityStat _upStat;
};

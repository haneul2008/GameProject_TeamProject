#pragma once

#include "Entity.h"
#include "IInputable.h"

class Player : virtual public Entity, virtual public IInputable
{
public:
    Player();

public:
    virtual void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) override;

    void setWhatIsItemLayer(int layer);
    void setWhatIsWallLayer(int layer);
    void setWhatIsEnemyLayer(int layer);

    void applyMove() override;

    // IInputable을(를) 통해 상속됨
    void onInputKey(Key key) override;
    void setInputLock(bool value);

private:
    void onTriggerEvent(Collider& other, const Pos& newPosition) override;
    void onCollisionEvent(Collider& other, const Pos& newPosition) override;
    void attack(Entity* target, int damage);
    // 굳이 저장할 필요가 없다고 느낌. 상시 차지하는 메모리만 커질 듯
    std::string getAttackComment();

private:
    bool _inputLock;

private:
    int _whatIsItem;
    int _whatIsWall;
    int _whatIsEnemy;
};
#pragma once

#include<memory>

#include "Entity.h"
#include "IInputable.h"
#include "FOV.h"

class Player : virtual public Entity, virtual public IInputable
{
public:
    Player();
    ~Player() override;
    virtual Player* newClone() override;

public:
    virtual void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) override;

    void setWhatIsItemLayer(int layer);
    void setWhatIsWallLayer(int layer);
    void setWhatIsEnemyLayer(int layer);
    void SetUp();

    void takeDamage(Entity* dealer, int damage) override;
    void applyMove() override;

    // IInputable을(를) 통해 상속됨
    void onInputKey(Key key) override;
    void setInputLock(bool value);

private:
    void onTriggerEvent(Collider& other, const Pos& newPosition) override;
    void onCollisionEvent(Collider& other, const Pos& newPosition) override;

    void setHpUI();

private:
    bool _inputLock;

private:
    int _whatIsItem;
    int _whatIsWall;
    int _whatIsEnemy;

private:
    std::unique_ptr<FOV> fov;
};
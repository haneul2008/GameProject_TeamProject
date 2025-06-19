#pragma once

#include "Entity.h"
#include "IInputable.h"

class Player : virtual public Entity, virtual public IInputable
{
public:
    Player();

public:
    void setWhatIsItemLayer(int layer);
    void setWhatIsWallLayer(int layer);
    void setWhatIsEnemyLayer(int layer);

    // IInputable을(를) 통해 상속됨
    void onInputKey(Key key) override;

private:
    int _whatIsItem;
    int _whatIsWall;
    int _whatIsEnemy;
};
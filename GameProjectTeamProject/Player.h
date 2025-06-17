#pragma once

#include "Entity.h"

class Player : virtual public Entity
{
public:
    void SetWhatIsItemLayer(int layer);
    void SetWhatIsWallLayer(int layer);
    void SetWhatIsEnemyLayer(int layer);

private:
    int _whatIsItem;
    int _whatIsWall;
    int _whatIsEnemy;
};
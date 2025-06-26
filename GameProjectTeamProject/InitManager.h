#pragma once

#include<vector>

#include "Player.h"
#include "Enemy.h"

class InitManager
{
public:
    InitManager();

private:
    Player _player;
    std::vector<Enemy> _enemies;
};


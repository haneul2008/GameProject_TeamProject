#pragma once

#include<vector>

#include "Player.h"
#include "Enemy.h"
#include "Singletone.h"

class InitManager : public Singleton<InitManager>
{
public:
    InitManager();
    void InitPlayer();
    void InitEnemies();
    void DeletePlayer();
private:
    Player* _pPlayer;
};


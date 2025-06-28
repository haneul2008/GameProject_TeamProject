#pragma once

#include<vector>
#include<string>

#include "Player.h"
#include "Enemy.h"
#include "Singletone.h"

const std::string ENEMY_DATA_POOL = "ENEMY";
const std::string ITEM_DATA_POOL = "ITEM";

class InitManager : public Singleton<InitManager>
{
public:
    InitManager();
    void InitPlayer();
    void InitEnemies();
    void InitItems();
    void DeletePlayer();
private:
    Player* _pPlayer;
};


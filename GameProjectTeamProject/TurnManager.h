#pragma once

#include <set>

#include "Singletone.h"

class ITurnListener
{
public:
    void virtual handlePlayerTurn() abstract;
    void virtual handleEnemyTurn() abstract;
};

class TurnManager : public Singleton<TurnManager>
{
public:
    void onPlayerTurn();
    void onEnemyTurn();

    void addTurnListener(ITurnListener* listener);

private:
    std::set<ITurnListener*> _turnListeners;
};
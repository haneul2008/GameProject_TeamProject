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
    void usePlayerTurn();
    void useEnemyTurn();

    void addTurnListener(ITurnListener* listener);
    void removeTurnListener(ITurnListener* listener);

private:
    std::set<ITurnListener*> _turnListeners;
};
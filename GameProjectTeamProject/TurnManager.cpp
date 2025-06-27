#include "TurnManager.h"

void TurnManager::usePlayerTurn() {
    for (ITurnListener* listener : _turnListeners)
        listener->handleEnemyTurn();
}

void TurnManager::useEnemyTurn() {
    for (ITurnListener* listener : _turnListeners)
        listener->handlePlayerTurn();
}

void TurnManager::addTurnListener(ITurnListener* listener) {
    _turnListeners.insert(listener);
}

void TurnManager::removeTurnListener(ITurnListener* listener) {
    _turnListeners.erase(listener);
}

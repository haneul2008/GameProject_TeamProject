#include "TurnManager.h"

void TurnManager::onPlayerTurn() {
    for (ITurnListener* listener : _turnListeners)
        listener->handlePlayerTurn();
}

void TurnManager::onEnemyTurn() {
    for (ITurnListener* listener : _turnListeners)
            listener->handleEnemyTurn();
}

void TurnManager::addTurnListener(ITurnListener* listener) {
    _turnListeners.insert(listener);
}

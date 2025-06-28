#include "TurnManager.h"

void TurnManager::usePlayerTurn() {
    for(int i = 0; i < _turnListeners.size(); ++i)
		_turnListeners[i]->handleEnemyTurn();
}

void TurnManager::useEnemyTurn() {
    for(int i = 0; i < _turnListeners.size(); ++i)
		_turnListeners[i]->handlePlayerTurn();
}

void TurnManager::addTurnListener(ITurnListener* listener) {
    _turnListeners.push_back(listener);
}

void TurnManager::removeTurnListener(ITurnListener* listener) {
	auto it = std::find(_turnListeners.begin(), _turnListeners.end(), listener);
    if (it == _turnListeners.end()) return;
    _turnListeners.erase(it);
}

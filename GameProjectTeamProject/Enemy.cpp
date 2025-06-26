#include "Enemy.h"

#include <format>

#include "UISupporter.h"

void Enemy::init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) {
    Entity::init(stat, defaultImage, trigger, layer);
}

void Enemy::active() {
    TurnManager::GetInstance()->addTurnListener(this);
}

void Enemy::handlePlayerTurn() {
}

void Enemy::handleEnemyTurn() {
}

void Enemy::onHitEvent(Entity* dealer, int damage) {
}

void Enemy::onDeadEvent(Entity* dealer, int damage) {
    std::string printComment = std::format("{}이(가) {}.", _name, getDeadMessage());
    std::wstring printMessage = to_wstring(printComment);
    pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);
}

void Enemy::addDeadMessage(std::string message) {
    _deadMassages.push_back(message);
}

std::string Enemy::getDeadMessage() {
    return _deadMassages[rand() % _deadMassages.size()];
}


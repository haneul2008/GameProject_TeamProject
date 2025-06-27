#include "Enemy.h"

#include <format>

#include "UISupporter.h"

Enemy::~Enemy() {
}

Enemy* Enemy::newClone() {
    return new Enemy(*this);
}

void Enemy::init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) {
    Entity::init(stat, defaultImage, trigger, layer);
}

void Enemy::active() {
    Entity::active();
    TurnManager::GetInstance()->addTurnListener(this);
}

void Enemy::deActive() {
    Entity::deActive();
    TurnManager::GetInstance()->removeTurnListener(this);
}

void Enemy::handlePlayerTurn() {
}

void Enemy::handleEnemyTurn() {
    if (!sencePlayerInSenceRange())
        return;

    Pos direction = getMoveToPlayerPos();
    _tempMoveX = direction.x;
    _tempMoveY = direction.y;

    applyMove();
}

void Enemy::onHitEvent(Entity* dealer, int damage) {
}

void Enemy::onDeadEvent(Entity* dealer, int damage) {
    std::string printComment = std::format("{}이(가) {}.", _name, getDeadMessage());
    std::wstring printMessage = to_wstring(printComment);
    pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);

    Entity::onDeadEvent(dealer, damage);
}

void Enemy::addDeadMessage(std::string message) {
    _deadMassages.push_back(message);
}

void Enemy::setPlayer(Player* player) {
    _player = player;
    _player->addDeadListener(this);
}

void Enemy::setSenceRange(int range) {
    _senceRange = range;
}

void Enemy::onCollisionEvent(Collider& other, const Pos& beforePosition) {
    if (_player == nullptr)
        return;

    if ((other.getLayer() & _player->getLayer()) != 0) {
        Entity* entity = dynamic_cast<Entity*>(&other);
        if (entity != nullptr && stat.damage >= 0)
            attack(entity, stat.damage);
    }
    
    Entity::onCollisionEvent(other, beforePosition);
}

std::string Enemy::getDeadMessage() {
    return _deadMassages[rand() % _deadMassages.size()];
}

bool Enemy::sencePlayerInSenceRange() {
    if (_player == nullptr)
        return false;

    Pos direction = *_player->getPosition() - pos;
    return direction.getMagnitude() <= _senceRange;
}

Pos&& Enemy::getMoveToPlayerPos() {
    Pos moveDistance = Pos();

    if (_player == nullptr)
        return std::move(moveDistance);

    Pos direction = *_player->getPosition() - pos;

    if (std::abs(direction.x) > std::abs(direction.y))
        moveDistance.x = direction.x;
    else
        moveDistance.y = direction.y;

    moveDistance.normalize();

    return std::move(moveDistance);
}

void Enemy::handleDeadEvent(Entity* deadEntity) {
    if (_player == deadEntity) {
        _player = nullptr;
        _player->removeDeadListener(this);
    }
}


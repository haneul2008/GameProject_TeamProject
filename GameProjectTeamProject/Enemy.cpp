#include "Enemy.h"

#include <format>

#include "UISupporter.h"
#include "Physics.h"
#include "StageManager.h"
#include "Mci.h"
#pragma comment(lib, "winmm")

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

void Enemy::Render() {
    if (StageManager::GetInstance()->GetStage()->curMap[pos.y][pos.x].isHide)
        return;

    Entity::Render();
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
	PlaySoundID(SOUNDID::PlayerAttack);
    Entity::onHitEvent(dealer, damage);
}

void Enemy::onDeadEvent(Entity* dealer, int damage) {
    std::string printComment = std::format("{}이(가) {}.", _name, getDeadMessage());
    std::wstring printMessage = to_wstring(printComment);
    pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);
    PlaySoundID(SOUNDID::EnemyDead);

    Entity::onDeadEvent(dealer, damage);
}

void Enemy::addDeadMessage(std::string message) {
    _deadMassages.push_back(message);
}

void Enemy::setPlayer(Player* player) {
    _pPlayer = player;
    _pPlayer->addDeadListener(this);
}

void Enemy::setSenceRange(int range) {
    _senceRange = range;
}

void Enemy::onCollisionEvent(Collider& other, const Pos& beforePosition) {
    if (_pPlayer == nullptr)
        return;

    if ((other.getLayer() & _pPlayer->getLayer()) != 0) {
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
    if (_pPlayer == nullptr)
        return false;

    Pos direction = *_pPlayer->getPosition() - pos;
    return direction.getMagnitude() <= _senceRange;
}

Pos Enemy::getMoveToPlayerPos() {
    Pos moveDistance = Pos();

    if (_pPlayer == nullptr)
        return moveDistance;

    Pos direction = *_pPlayer->getPosition() - pos;

    if (std::abs(direction.x) > std::abs(direction.y))
        moveDistance.x = direction.x;
    else
        moveDistance.y = direction.y;

    moveDistance.normalize();

    Pos check = pos + moveDistance;
    Collider* collider = PhysicsManager::GetInstance()->getCollider(*this, check);
    if (collider != nullptr
        && !collider->getIsTrigger()
        && (collider->getLayer() & _whatIsWall) != 0) {

        if (std::abs(direction.x) > std::abs(direction.y)) {
            moveDistance.x = 0;
            moveDistance.y = direction.y;
        }
        else {
            moveDistance.y = 0;
            moveDistance.x = direction.x;
        }
    }

    moveDistance.normalize();

    return moveDistance;
}

void Enemy::handleDeadEvent(Entity* deadEntity) {
    if (_pPlayer == deadEntity) {
        _pPlayer->removeDeadListener(this);
        _pPlayer = nullptr;
    }
}

void Enemy::setWallLayer(int layer) {
    _whatIsWall = layer;
}


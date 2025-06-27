#include "Player.h"

#include <format>
#include "UISupporter.h"

#include "InputSystem.h"
#include "TurnManager.h"
#include "IDamageable.h"

Player::Player() :
    _whatIsItem(0),
    _whatIsWall(0),
    _whatIsEnemy(0),
    _inputLock(false) {
}

Player::~Player() {
    InputManager::GetInstance()->removeInputListener(this);
}

Player* Player::newClone() {
    // 복사를 불가능하게 하기위함.
    return nullptr;
}

void Player::init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) {
    Entity::init(stat, defaultImage, trigger, layer);
    InputManager::GetInstance()->addInputListener(this);
}

void Player::setWhatIsItemLayer(int layer) {
    _whatIsItem = layer;
}

void Player::setWhatIsWallLayer(int layer) {
    _whatIsWall = layer;
}

void Player::setWhatIsEnemyLayer(int layer) {
    _whatIsEnemy = layer;
}

void Player::applyMove() {
    bool move = _tempMoveX != 0 || _tempMoveY != 0;

    Entity::applyMove();

    if (move) {
        // move 애니메이션으로 변경
        render.setCurrentAnimation('m');
        TurnManager::GetInstance()->usePlayerTurn();
    }
    else
        render.setCurrentAnimation('i');
}

void Player::onInputKey(Key key) {
    if (_inputLock)
        return;

    switch (key) {
        case Key::UP:
            moveY(-1);
            break;
        case Key::DOWN:
            moveY(1);
            break;
        case Key::LEFT:
            moveX(-1);
            break;
        case Key::RIGHT:
            moveX(1);
            break;
        case Key::INTERACT:
            break;
    }
}

void Player::setInputLock(bool value) {
    _inputLock = value;
}

void Player::onTriggerEvent(Collider& other, const Pos& previousPos) {
}

void Player::onCollisionEvent(Collider& other, const Pos& previousPos) {
    int collisionLayer = other.getLayer();

    if ((collisionLayer & _whatIsEnemy) != 0) {
        Entity* entity = dynamic_cast<Entity*>(&other);
        if (entity != nullptr && stat.damage >= 0) {
            // 10%정도 추가 피해 0 ~ 10%
            int damagePer = stat.damage / stat.addDamagePer;
            int randDamage = rand() % (damagePer == 0 ? 1 : damagePer);
            attack(entity, stat.damage + randDamage);
        }
    }

    Entity::onCollisionEvent(other, previousPos);
}
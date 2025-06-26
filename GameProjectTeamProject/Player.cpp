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
    if (_tempMoveX != 0 || _tempMoveY != 0) {
        // move 애니메이션으로 변경
        render.setCurrentAnimation('m');
        TurnManager::GetInstance()->onPlayerTurn();
    }
    else
        render.setCurrentAnimation('i');

    Entity::applyMove();
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

    pos = previousPos;

    if ((collisionLayer & _whatIsEnemy) != 0) {
        Entity* entity = dynamic_cast<Entity*>(&other);
        if (entity != nullptr && _entityStat.damage >= 0) {
            // 10%정도 추가 피해 0 ~ 10%
            int damagePer = _entityStat.damage / _entityStat.addDamagePer;
            int randDamage = rand() % (damagePer == 0 ? 1 : damagePer);
            attack(entity, _entityStat.damage + randDamage);
        }
    }
}

void Player::attack(Entity* target, int damage) {
    std::string printComment = std::format("{}이(가) {}에게 {}. 피해 : {}", _name, target->getName(), getAttackComment(), damage);
    std::wstring printMessage = to_wstring(printComment);
    pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);

    target->takeDamage(this, damage);
}

// 굳이 따로 빼서 관리할 필요 없음 플레이어는 유일하며, 따로 메모리에 계속남게 할 필요 없음
std::string Player::getAttackComment() {
    std::vector<std::string> comments;

    // 무겁게
    comments.push_back("칼날을 적의 피부 깊숙이 박아 끔찍한 고통을 선사했다");
    comments.push_back("적의 살점을 찢어내며 잔혹하게 공격했다");
    comments.push_back("붉은 피가 튀는 소리와 함께 맹공을 퍼부었다");
    comments.push_back("공포를 알려줬다");
    comments.push_back("적의 살갗을 찢어 피를 흐르게 했다");
    comments.push_back("결의 찬 회심의 일격을 가했다");
    comments.push_back("배에 칼을 박고 돌려 내장이 쏟아지게끔 했다");

    // 재밌게
    comments.push_back("너무 약한 공격을 하여 적의 혈압을 높였다");
    comments.push_back("차마 입에 담기 꺼려지는 인신공격을 가했다");
    comments.push_back("공격을 했지만 실패했다... 실패한 공격이 적의 새끼발톱을 쳐 끔찍한 고통을 가했다");
    comments.push_back("균형을 잃어 적어게 넘어져 너무 가까운 거리에 적의 심박수가 올라갔다");
    comments.push_back("음심에 가득한 신체접촉을 했다");

    return comments[rand() % comments.size()];
}
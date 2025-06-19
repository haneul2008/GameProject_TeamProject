#include "Player.h"

#include "InputManager.h"

Player::Player() :
    _whatIsItem(0),
    _whatIsWall(0),
    _whatIsEnemy(0) {
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
    if (_tempMoveX != 0 || _tempMoveY != 0)
        // move 애니메이션으로 변경
        render.setCurrentAnimation('m');
    else
        render.setCurrentAnimation('i');
    Entity::applyMove();
}

void Player::onInputKey(Key key) {
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

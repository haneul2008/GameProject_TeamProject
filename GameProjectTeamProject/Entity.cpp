#include "Entity.h"

Entity::~Entity() {
}

void Entity::Move(int x, int y) {
    MoveX(x);
    MoveY(y);
}

void Entity::Move(const Pos& pos) {
    Move(pos.x, pos. y);
}

void Entity::MoveX(int value) {
    _tempMoveX = value;
}

void Entity::MoveY(int value) {
    _tempMoveY = value;
}

void Entity::Update() {
    Pos tempPos = pos;
    tempPos.x += _tempMoveX;
    tempPos.y += _tempMoveY;

    tryCollision(tempPos);
}

int Entity::GetPriotity() {
    return 0;
}

void Entity::onTriggerEvent(const Collider& other, const Pos& beforePosition) {
}

void Entity::onCollisionEvent(const Collider& other, const Pos& beforePosition) {
}

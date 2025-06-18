#include "Entity.h"

#include "Core.h"

Entity::Entity() {
    Core::GetInstance()->AddUpdate(this);
}

Entity::~Entity() {
}

void Entity::init(wchar_t defaultImage, bool trigger, int layer) {
    pos = Pos();
    Collider::init(&pos, trigger, layer);
    Object::setDefaultImage(defaultImage);
}

void Entity::setPosition(const Pos& pos) {
    this->pos = pos;
}

void Entity::move(int x, int y) {
    moveX(x);
    moveY(y);
}

void Entity::move(const Pos& pos) {
    move(pos.x, pos. y);
}

void Entity::moveX(int value) {
    _tempMoveX = value;
}

void Entity::moveY(int value) {
    _tempMoveY = value;
}

void Entity::Update() {
    Pos tempPos = pos;
    tempPos.x += _tempMoveX;
    tempPos.y += _tempMoveY;

    _tempMoveX = 0;
    _tempMoveY = 0;

    PhysicsManager* physicsManager = PhysicsManager::GetInstance();

    int maxWidth = physicsManager->getMaxWidth();
    int maxHeight = physicsManager->getMaxHeight();

    if (tempPos.x < 0 || tempPos.y < 0 ||
        tempPos.x >= maxWidth ||
        tempPos.y >= maxHeight)
        return;

    if (!tryCollision(tempPos))
        pos = tempPos;
}

int Entity::GetUpdatePriotity() {
    return _updatePriority;
}

void Entity::SetUpdatePriotity(int priority) {
    _updatePriority = priority;
}

void Entity::onTriggerEvent(const Collider& other, const Pos& newPosition) {
}

void Entity::onCollisionEvent(const Collider& other, const Pos& newPosition) {
}

#include "Physics.h"

PhysicsManager::PhysicsManager(int maxHieght, int maxWidth)
    :_maxHeight(maxHieght),
    _maxWidth(maxWidth) {
    for (int y = 0; y < _maxHeight; ++y) {
        _physicsMap[y] = new Collider * [_maxWidth];
        for (int x = 0; x < _maxWidth; ++x)
            _physicsMap[y][x] = nullptr;
    }
}

PhysicsManager::~PhysicsManager() {
    for (int y = 0; y < _maxHeight; ++y) {
        delete[] _physicsMap[y];
    }
    delete[] _physicsMap;
}

const Collider* PhysicsManager::getCollider(int x, int y) {
    if (y < 0 || y >= _maxHeight || x < 0 || x >= _maxWidth)
        return nullptr;

    return _physicsMap[y][x];
}

const Collider* PhysicsManager::getCollider(const Pos& pos) {
    return this->getCollider(pos.x, pos.y);
}

void PhysicsManager::setCollider(Collider* collider, int x, int y) {
    if (y < 0 || y >= _maxHeight || x < 0 || x >= _maxHeight)
        return;

    _physicsMap[y][x] = collider;
}

void PhysicsManager::setCollider(Collider* collider, const Pos& pos) {
    return this->setCollider(collider, pos.x, pos.y);
}

Collider::Collider(pPos pos, bool trigger, int layer)
    : _position(pos),
    _isTrigger(trigger),
    _layer(layer) {
}


Collider::~Collider() {

}

int Collider::getCollidedObjectLayer(const Collider& other) {
    bool collision = calculateCollision(other);
    return collision ? isOverlapLayer(other.getLayer()) : 0;
}

bool Collider::isAnyTrigger(const Collider& other) const {
    return this->_isTrigger || other.getIsTrigger();
}

bool Collider::isOverlapLayer(int layer) const {
    return (this->_layer & layer) != 0;
}

bool Collider::getIsTrigger() const {
    return _isTrigger;
}

int Collider::getLayer() const {
    return _layer;
}

void Collider::setLayer(int layer) {
    _layer = layer;
}

pPos Collider::getPosition() const {
    return _position;
}

void Collider::setPosition(pPos position) {
    _position = position;
}


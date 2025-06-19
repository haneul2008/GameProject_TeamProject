#include "Physics.h"

PhysicsManager::PhysicsManager() {
}

PhysicsManager::~PhysicsManager() {
    for (int y = 0; y < _maxHeight; ++y) {
        delete[] _physicsMap[y];
    }
    delete[] _physicsMap;
}

void PhysicsManager::initialize(int maxHieght, int maxWidth) {
    _maxHeight = maxHieght;
    _maxWidth = maxWidth;

    _physicsMap = new Collider * *[_maxWidth];
    for (int x = 0; x < _maxWidth; ++x) {
        _physicsMap[x] = new Collider * [_maxHeight];
        for (int y = 0; y < _maxHeight; ++y) {
            _physicsMap[x][y] = nullptr;
        }
    }
}

const Collider* PhysicsManager::getCollider(int x, int y) const {
    if (y < 0 || y >= _maxHeight || x < 0 || x >= _maxWidth)
        return nullptr;

    return _physicsMap[y][x];
}

const Collider* PhysicsManager::getCollider(const Pos& pos) const {
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

int PhysicsManager::getMaxHeight() {
    return _maxHeight;
}

int PhysicsManager::getMaxWidth() {
    return _maxWidth;
}

Collider::Collider():
_isTrigger(false),
_layer(0) {
}

Collider::~Collider() {
}

void Collider::init(pPos pPos, bool trigger, int layer) {
    _position = pPos;
    _isTrigger = trigger;
    _layer = layer;
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

bool Collider::tryCollision(const Pos& pos) {
    const PhysicsManager* physicsManager = PhysicsManager::GetInstance();

    const Collider* collider = (*physicsManager).getCollider(pos);
    if (collider != nullptr) {
        bool collision = calculateCollision(*collider);
        bool triggerCollsition = isAnyTrigger(*collider);

        if (collision) {
            if (triggerCollsition)
                onTriggerEvent(*collider, pos);
            else
                onCollisionEvent(*collider, pos);

            return true;
        }
    }

    return false;
}


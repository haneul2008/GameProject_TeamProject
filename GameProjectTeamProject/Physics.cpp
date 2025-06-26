#include "Physics.h"

PhysicsManager::PhysicsManager() {
}

PhysicsManager::~PhysicsManager() {
}

void PhysicsManager::setMaxMoveBound(int x, int y) {
    _maxHeight = y;
    _maxWidth = x;
}

Collider* PhysicsManager::getCollider(const Collider& owner, int x, int y) const {
    return this->getCollider(owner, {x, y});
}

Collider* PhysicsManager::getCollider(const Collider& owner, const Pos& pos) const {
    for (Collider* collider : _collisers) {
        if (*collider->getPosition() == pos && &owner != collider)
            return collider;
    }
    return nullptr;
}

void PhysicsManager::addCollider(Collider* collider) {
    _collisers.push_back(collider);
}

int PhysicsManager::getMaxHeight() {
    return _maxHeight;
}

int PhysicsManager::getMaxWidth() {
    return _maxWidth;
}

Collider::Collider():
_isTrigger(false),
_layer(0),
_pPosition(nullptr){
}

Collider::~Collider() {
}

void Collider::init(pPos pPos, bool trigger, int layer) {
    _pPosition = pPos;
    _isTrigger = trigger;
    _layer = layer;
}

void Collider::active() {
    PhysicsManager::GetInstance()->addCollider(this);
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
    return _pPosition;
}

void Collider::setPosition(pPos position) {
    _pPosition = position;
}

bool Collider::tryCollision(const Pos& previousPos, const Pos& pos) {
    const PhysicsManager* physicsManager = PhysicsManager::GetInstance();

    Collider* collider = (*physicsManager).getCollider(*this, pos);
    if (collider != nullptr) {
        bool collision = calculateCollision(*collider);

        if (collision) {
            bool triggerCollsition = isAnyTrigger(*collider);
            if (triggerCollsition)
                onTriggerEvent(*collider, previousPos);
            else
                onCollisionEvent(*collider, previousPos);

            return true;
        }
    }

    return false;
}


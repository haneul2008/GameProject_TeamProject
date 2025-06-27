#include "Colliders.h"

PositionCollider::~PositionCollider() {
}

bool PositionCollider::calculateCollision(const Collider& other) const {
    return *getPosition() == *other.getPosition();
}
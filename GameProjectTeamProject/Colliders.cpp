#include "Colliders.h"

bool PositionCollider::calculateCollision(const Collider& other) const {
    return *getPosition() == *other.getPosition();
}
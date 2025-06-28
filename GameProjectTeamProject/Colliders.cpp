#include "Colliders.h"

PositionCollider::~PositionCollider() {
}

bool PositionCollider::calculateCollision(const Collider& other) const {
    return *getPosition() == *other.getPosition();
}

void PositionCollider::onTriggerEvent(Collider& other, const Pos& beforePosition) {
}

void PositionCollider::onCollisionEvent(Collider& other, const Pos& beforePosition) {
}

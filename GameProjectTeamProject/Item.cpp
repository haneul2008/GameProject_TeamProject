#include "Item.h"

void Item::onTriggerEvent(Collider& other, const Pos& beforePosition) {
}

void Item::onCollisionEvent(Collider& other, const Pos& beforePosition) {
}

void Item::init( wchar_t defaultImage, bool trigger, int layer) {
    Object::init();
    Object::setDefaultImage(defaultImage);

    pos = Pos();
    Collider::init(&pos, trigger, layer);
}

void Item::active() {
    Collider::active();
    Collider::setPosition(&pos);
    Object::active();
}

void Item::deActive() {
    Collider::deActive();
    Collider::setPosition(nullptr);
    Object::deActive();
}

void Item::setPosition(const Pos& pos) {
    this->pos = pos;
}

void Item::setName(std::string name) {
    _name = name;
}

std::string Item::getName() const {
    return _name;
}

// Item=========================================

void StatItem::setUpStat(const EntityStat& stat) {
    _upStat = stat;
}

void StatItem::useItem(Entity* itemUser) {
    itemUser->stat = itemUser->stat + _upStat;
}

#include "Item.h"

#include "StageManager.h"

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
    Collider::setOriginPosition(&pos);
    Object::active();
}

void Item::deActive() {
    Collider::deActive();
    Collider::setOriginPosition(nullptr);
    Object::deActive();
}

Item* Item::newClone() {
    // item자체는 nullptr반환 상속 객체가 newClone가능하게 할것
    return nullptr;
}

void Item::Render() {
    if (StageManager::GetInstance()->GetStage()->curMap[pos.y][pos.x].isHide)
        return;

    Object::Render();
}

void Item::setName(std::string name) {
    _name = name;
}

std::string Item::getName() const {
    return _name;
}

bool Item::isPick() {
    return _picked;
}

void Item::pick() {
    _picked = true;
}

void Item::useItem(Entity* itemUser) {
    itemUser->onUseItem();
}

// Item=========================================

StatItem* StatItem::newClone() {
    return new StatItem(*this);
}

void StatItem::setUpStat(const EntityStat& stat) {
    _upStat = stat;
}

void StatItem::useItem(Entity* itemUser) {
    itemUser->stat = itemUser->stat + _upStat;
    Item::useItem(itemUser);
}

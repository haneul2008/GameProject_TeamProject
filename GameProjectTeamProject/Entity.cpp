#include "Entity.h"

#include <algorithm>
#include <cstdlib>
#include <format>

#include "Core.h"
#include "InputSystem.h"
#include "UISupporter.h"

Entity::Entity() :
    _entityStat(EntityStat()),
    _tempMoveX(0),
    _tempMoveY(0),
    _updatePriority(0) {
}

Entity::~Entity() {
}

Entity::Entity(Entity&& other) :
    _entityStat(EntityStat()),
    _tempMoveX(0),
    _tempMoveY(0),
    _updatePriority(0) {
}

Entity::Entity(const Entity& other)
    : Object(other), Collider(other),
    _entityStat(other._entityStat),
    _name(other._name),
    _tempMoveX(0),
    _tempMoveY(0),
    _updatePriority(other._updatePriority) {
    Collider::init(&pos, other.getIsTrigger(), other.getLayer());
}

void Entity::init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) {
    Object::init();
    Object::setDefaultImage(defaultImage);

    pos = Pos();
    _entityStat = stat;

    Collider::init(&pos, trigger, layer);
}

void Entity::active() {
    Collider::active();
    Object::active();
    Core::GetInstance()->AddUpdate(this);
}

void Entity::deActive() {
    Collider::active();
    Object::active();
    // 여기도 제거 필요
    //Core::GetInstance()->AddUpdate(this);
}

void Entity::setPosition(const Pos& pos) {
    this->pos = pos;
}

void Entity::move(int x, int y) {
    moveX(x);
    moveY(y);
}

void Entity::move(const Pos& pos) {
    move(pos.x, pos.y);
}

void Entity::moveX(int value) {
    _tempMoveX = value;
}

void Entity::moveY(int value) {
    _tempMoveY = value;
}

void Entity::applyMove() {
    previousPos = pos;
    pos.x += _tempMoveX;
    pos.y += _tempMoveY;

    _tempMoveX = 0;
    _tempMoveY = 0;

    PhysicsManager* physicsManager = PhysicsManager::GetInstance();

    int maxWidth = physicsManager->getMaxWidth();
    int maxHeight = physicsManager->getMaxHeight();

    if (pos == previousPos ||
        pos.x < 0 ||
        pos.y < 0 ||
        pos.x >= maxWidth ||
        pos.y >= maxHeight)
        return;

    tryCollision(previousPos, pos);
}

const EntityStat Entity::getStat() const {
    return _entityStat;
}

void Entity::Update() {
    applyMove();
}

int Entity::GetUpdatePriotity() {
    return _updatePriority;
}

void Entity::SetUpdatePriotity(int priority) {
    _updatePriority = priority;
}

void Entity::onTriggerEvent(Collider& other, const Pos& previousPos) {
}

void Entity::onCollisionEvent(Collider& other, const Pos& previousPos) {
    // 만약 충돌 했으면 전 위치로 이동 기본 값으로 해두고, 후에 구현할 때 덮어쓰는 방식으로 사용.
    pos = previousPos;
}

void Entity::takeDamage(Entity* dealer, int damage) {
    if (damage <= 0) { // 회복 시
        _entityStat.hp = std::min(_entityStat.hp - damage, _entityStat.maxHp);

        std::string healMassage = std::format("{}이(가) {}에 의해 {}의 체력을 회복했습니다.", _name, dealer->getName(), -damage);
        std::wstring printMessage = to_wstring(healMassage);
        pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);

        return;
    }

    int attackSuccess = rand() % 101;

    if (_entityStat.avoidance <= attackSuccess)
        _entityStat.hp = std::max(_entityStat.hp - damage, 0);

    if (_entityStat.hp > 0)
        onHitEvent(dealer, damage);
    else
        onDeadEvent(dealer, damage);
}

void Entity::onHitEvent(Entity* dealer, int damage) {
}

void Entity::onDeadEvent(Entity* dealer, int damage) {
    for (IDeadHandler* listener : _deadListeners)
        listener->handleDeadEvent(this);
}

void Entity::addDeadListener(IDeadHandler* deadListener) {
    if (deadListener != nullptr)
        _deadListeners.insert(deadListener);
}

void Entity::removeDeadListener(IDeadHandler* deadListener) {
    _deadListeners.erase(deadListener);
}

void Entity::setName(std::string name) {
    _name = name;
}

std::string Entity::getName() {
    return _name;
}

EntityStat EntityStat::makeStat(int damage, int maxHp, int avoidance, int addDamagePer) {
    EntityStat stat;
    stat.damage = damage;
    stat.maxHp = maxHp;
    stat.hp = maxHp;
    stat.avoidance = avoidance;
    stat.addDamagePer = addDamagePer;
    return stat;
}
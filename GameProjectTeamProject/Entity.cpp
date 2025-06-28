#include "Entity.h"

#include <algorithm>
#include <cstdlib>
#include <format>

#include "Core.h"
#include "InputSystem.h"
#include "UISupporter.h"

Entity::Entity() :
	stat(EntityStat()),
	_tempMoveX(0),
	_tempMoveY(0),
	_updatePriority(0),
	_isDead(false) {
}

Entity::~Entity() {
}

Entity::Entity(Entity&& other) :
	stat(EntityStat()),
	_tempMoveX(0),
	_tempMoveY(0),
	_updatePriority(0),
	_isDead(false) {
}

Entity::Entity(const Entity& other)
	: Object(other), Collider(other),
	stat(other.stat),
	_name(other._name),
	_tempMoveX(0),
	_tempMoveY(0),
	_updatePriority(other._updatePriority),
	_attckComments(other._attckComments),
	_isDead(false) {
	Collider::init(&pos, other.getIsTrigger(), other.getLayer());
}

Entity* Entity::newClone() {
	return new Entity(*this);
}

void Entity::init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) {
	Object::init();
	Object::setDefaultImage(defaultImage);

	pos = Pos();
	this->stat = stat;
	Collider::init(&pos, trigger, layer);
}

void Entity::active() {
	Collider::active();
	Collider::setOriginPosition(&pos);
	Object::active();
	Core::GetInstance()->AddUpdate(this);
}

void Entity::deActive() {
	Collider::deActive();
	Object::deActive();
	Core::GetInstance()->RemoveUpdate(this);
	_deadListeners.clear();
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
		pos.y >= maxHeight) {
		pos = previousPos;
		return;
	}

	tryCollision(previousPos);
}

const EntityStat Entity::getStat() const {
	return stat;
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

std::string Entity::getAttackComment() const {
	return _attckComments[rand() % _attckComments.size()];
}

void Entity::takeDamage(Entity* dealer, int damage) {
	if (damage == 0 || _isDead)
		return;

	if (damage <= 0) { // 회복 시 damage가 음수일 때
		stat.hp = std::min(stat.hp - damage, stat.maxHp);

		std::string healMassage = std::format("{}이(가) {}에 의해 {}의 체력을 회복했습니다.", _name, dealer->getName(), -damage);
		std::wstring printMessage = to_wstring(healMassage);
		pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);
	}
	else {
		int evade = rand() % 1001;
		if (evade <= stat.evadePer) {

			std::string healMassage = std::format("{}이(가) {}의 공격을 회피했다.", _name, dealer->getName());
			std::wstring printMessage = to_wstring(healMassage);
			pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);

			return;
		}

		stat.hp = std::max(stat.hp - damage, 0);

		if (stat.hp > 0)
			onHitEvent(dealer, damage);
		else
			onDeadEvent(dealer, damage);
	}
}

void Entity::onHitEvent(Entity* dealer, int damage) {
}

void Entity::onDeadEvent(Entity* dealer, int damage) {
	if (_isDead)
		return;

	_isDead = true;

	while (!_removeToListeners.empty()) {
		_deadListeners.erase(_removeToListeners.front());
		_removeToListeners.pop();
	}

	if (_deadListeners.size() > 0)
		for (IDeadHandler* listener : _deadListeners)
			if (listener != nullptr)
				listener->handleDeadEvent(this);

	while (!_removeToListeners.empty()) {
		_deadListeners.erase(_removeToListeners.front());
		_removeToListeners.pop();
	}
}

void Entity::addDeadListener(IDeadHandler* deadListener) {
	if (deadListener != nullptr)
		_deadListeners.insert(deadListener);
}

void Entity::removeDeadListener(IDeadHandler* deadListener) {
	_removeToListeners.push(deadListener);
}

void Entity::setName(std::string name) {
	_name = name;
}

std::string Entity::getName() {
	return _name;
}

void Entity::addAttackComment(const std::string& comment) {
	_attckComments.push_back(comment);
}

void Entity::attack(Entity* target, int damage) {
	if (_isDead)
		return;

	std::string printComment = std::format("{}이(가) {}에게 {}. 피해 : {}", _name, target->getName(), getAttackComment(), damage);
	std::wstring printMessage = to_wstring(printComment);
	pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);

	target->takeDamage(this, damage);
}

bool Entity::getIsdead() const {
	return _isDead;
}

void Entity::onUseItem() {
}

void Entity::multifyStat(float value) {
	stat = stat * value;
}

EntityStat EntityStat::operator+(const EntityStat& other) const {
	EntityStat newEntityStat = EntityStat();
	newEntityStat.damage = damage + other.damage;
	newEntityStat.maxHp = maxHp + other.maxHp;
	newEntityStat.hp = hp + other.hp;
	newEntityStat.evadePer = evadePer + other.evadePer;
	newEntityStat.addDamagePer = addDamagePer + other.addDamagePer;
	return newEntityStat;
}

EntityStat EntityStat::operator*(const float& value) const {
	EntityStat newEntityStat = EntityStat();
	newEntityStat.damage = static_cast<int>(std::round(damage * value));
	newEntityStat.addDamagePer = static_cast<int>(std::round(addDamagePer * value));
	newEntityStat.evadePer = static_cast<int>(std::round(evadePer * value));
	newEntityStat.hp = static_cast<int>(std::round(hp * value));
	newEntityStat.maxHp = static_cast<int>(std::round(maxHp * value));
	return newEntityStat;
}

EntityStat EntityStat::makeStat(int damage, int maxHp, int avoidance, int addDamagePer, int hp) {
	EntityStat stat;
	stat.damage = damage;
	stat.maxHp = maxHp;
	stat.hp = hp < 0 ? maxHp : hp;
	stat.evadePer = avoidance;
	stat.addDamagePer = addDamagePer;
	return stat;
}
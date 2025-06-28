#include "Player.h"

#include <string>
#include <format>
#include "UISupporter.h"

#include "InputSystem.h"
#include "TurnManager.h"
#include "IDamageable.h"
#include "StageManager.h"
#include "Item.h"
#include "InventoryManager.h"
#include "Constants.h"
#include "Mci.h"
#pragma comment(lib, "winmm")

const std::string HP_UI = "HP_UI";

Player::Player() :
    _whatIsItem(0),
    _whatIsWall(0),
    _whatIsEnemy(0),
    _inputLock(false) {
}

Player::~Player() {
    InputManager::GetInstance()->removeInputListener(this);
}

Player* Player::newClone() {
    // 복사를 불가능하게 하기위함.
    return nullptr;
}

void Player::init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) {
    Entity::init(stat, defaultImage, trigger, layer);
    InputManager::GetInstance()->addInputListener(this);

    SetUp();
    setHpUI();
}

void Player::setWhatIsItemLayer(int layer) {
    _whatIsItem = layer;
}

void Player::setWhatIsWallLayer(int layer) {
    _whatIsWall = layer;
}

void Player::setWhatIsEnemyLayer(int layer) {
    _whatIsEnemy = layer;
}

void Player::SetUp() {
    StageManager* stageManager = StageManager::GetInstance();
    fov = std::make_unique<FOV>(stageManager->GetStage(), stageManager->GetStage()->rooms);

    setPosition(stageManager->GetStage()->startPos);
    fov->UpdateFov(pos);
}

void Player::takeDamage(Entity* dealer, int damage) {
    Entity::takeDamage(dealer, damage);

	PlaySoundID(SOUNDID::PlayerHit);
    setHpUI();
}

void Player::applyMove() {
    bool move = _tempMoveX != 0 || _tempMoveY != 0;

    Entity::applyMove();

    if (move) {
        // move 애니메이션으로 변경
        render.setCurrentAnimation('m');
        TurnManager::GetInstance()->usePlayerTurn();
        fov.get()->UpdateFov(pos);

        if (StageManager::GetInstance()->CheckGoal(pos))
            SetUp();
    }
    else
        render.setCurrentAnimation('i');
}

void Player::onInputKey(Key key) {
    if (_inputLock)
        return;

    switch (key) {
        case Key::UP:
            moveY(-1);
            break;
        case Key::DOWN:
            moveY(1);
            break;
        case Key::LEFT:
            moveX(-1);
            break;
        case Key::RIGHT:
            moveX(1);
            break;
        case Key::INTERACT:
            break;
            // 이게 무슨 무식함의 극치란 말인가..?
        case Key::ONE:
            InventoryManager::GetInstance()->useItem(this, 1);
            break;
        case Key::TWO:
            InventoryManager::GetInstance()->useItem(this, 2);
            break;
        case Key::THREE:
            InventoryManager::GetInstance()->useItem(this, 3);
            break;
        case Key::FOUR:
            InventoryManager::GetInstance()->useItem(this, 4);
            break;
        case Key::FIVE:
            InventoryManager::GetInstance()->useItem(this, 5);
            break;
        case Key::SIX:
            InventoryManager::GetInstance()->useItem(this, 6);
            break;
        case Key::SEVEN:
            InventoryManager::GetInstance()->useItem(this, 7);
            break;
        case Key::EIGHT:
            InventoryManager::GetInstance()->useItem(this, 8);
            break;
        case Key::NINE:
            InventoryManager::GetInstance()->useItem(this, 9);
            break;
    }
}

void Player::setInputLock(bool value) {
    _inputLock = value;
}

void Player::onUseItem() {
    setHpUI();
}

void Player::onTriggerEvent(Collider& other, const Pos& previousPos) {
    int collisionLayer = other.getLayer();

    if ((collisionLayer & _whatIsItem) != 0) {
        Item* item = dynamic_cast<Item*>(&other);
        if (item != nullptr && stat.damage >= 0) {
            bool pick = InventoryManager::GetInstance()->tryAddItem(item);

            std::string printComment = pick
                ? std::format("{}이(가) {}를(을) 주었다.", _name, item->getName())
                : std::format("{}이(가) {}를(을) 주으려 했으나 실패했다.", _name, item->getName());
            std::wstring printMessage = to_wstring(printComment);
            pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);
        }
    }

    Entity::onTriggerEvent(other, previousPos);
}

void Player::onCollisionEvent(Collider& other, const Pos& previousPos) {
    int collisionLayer = other.getLayer();

    if ((collisionLayer & _whatIsEnemy) != 0) {
        Entity* entity = dynamic_cast<Entity*>(&other);
        if (entity != nullptr && stat.damage >= 0) {
            // 10%정도 추가 피해 0 ~ 10%
            int damagePer = stat.damage / stat.addDamagePer;
            int randDamage = rand() % (damagePer == 0 ? 1 : damagePer);
            attack(entity, stat.damage + randDamage);
        }
    }

    Entity::onCollisionEvent(other, previousPos);
}

void Player::setHpUI() {
    std::string str = std::format("HP : {} / {}", stat.hp, stat.maxHp);
    std::wstring wstr = to_wstring(str);
    UISupporter::GetInstance()->setUI(HP_UI, wstr);
    UISupporter::GetInstance()->setUI(HP_UI, (MAP_HEIGHT / 2) - (str.size() / 2), MAP_HEIGHT + 1);
}

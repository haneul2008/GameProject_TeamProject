#include "InventoryManager.h"

#include<string>
#include<format>

#include "UISupporter.h"
#include "Constants.h"
#include "Core.h"

constexpr std::string INVEN(int i) { return "INVEN" + std::to_string(i); }
constexpr int INTERVAL = 10;

InventoryManager::InventoryManager() :
    _maxInven(0) {
    Core::GetInstance()->AddUpdate(this);

    InputManager::GetInstance()->addInputListener(this);
}

InventoryManager::~InventoryManager() {
    for (Item* item : _inventory)
        delete item;

    Core::GetInstance()->RemoveUpdate(this);
    InputManager::GetInstance()->removeInputListener(this);
}

void InventoryManager::init(int maxIven) {
    _maxInven = maxIven;
}

bool InventoryManager::tryAddItem(Item* item) {
    if (_maxInven <= _inventory.size())
        return false;

    item->pick();

    _inventory.push_back(item);
    _deActivationQueue.push(item);
    resetItemUI();
}

void InventoryManager::Update() {
    while (!_deActivationQueue.empty()) {
        _deActivationQueue.front()->deActive();
        _deActivationQueue.pop();
    }
}

int InventoryManager::GetUpdatePriotity() {
    return 2147483647;
}

// 번째 접근임. 인덱스 순서 접근이 아님
bool InventoryManager::useItem(Entity* user, int i) {
    if (--i < 0 || _inventory.size() <= i)
        return false;

    std::string itemName = _inventory[i]->getName();

    _inventory[i]->useItem(user);
    // 사용 후 제거
    delete _inventory[i];
    _inventory.erase(_inventory.begin() + i);
    UISupporter::GetInstance()->removeUI(INVEN(i));

    resetItemUI();

    std::string printComment = std::format("{}이(가) {}를(을) 사용했다.", user->getName(), itemName);
    std::wstring printMessage = to_wstring(printComment);
    pauseToWaitKeyAndPrint(Key::ENDINPUT, printMessage);

    return true;
}

void InventoryManager::resetItemUI() {
    // 전부 리셋해버려서 비효율적, 수정시 고정 인덱스로 접근 시켜야 할듯
    for (int i = 1; i <= _inventory.size(); ++i) {
        std::string str = std::format("{} : {}", i, _inventory[i - 1]->getName());
        std::wstring wstr = to_wstring(str);
        UISupporter::GetInstance()->setUI(INVEN(i), wstr);
        UISupporter::GetInstance()->setUI(INVEN(i), (i - 1) * INTERVAL, MAP_HEIGHT + 2);
    }
}

void InventoryManager::onInputKey(Key key) {
    switch (key) {
        case Key::OPENINVEN: {
            _openIven = !_openIven;

            if (_openIven)
                resetItemUI();
            else
                for (int i = 1; i <= _inventory.size(); ++i)
                    UISupporter::GetInstance()->removeUI(INVEN(i));
        }
        default:
            break;
    }
}

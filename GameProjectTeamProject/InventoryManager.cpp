#include "InventoryManager.h"

#include<string>
#include<format>

#include "UISupporter.h"
#include "Core.h"

constexpr std::string INVEN(int i) { return "INVEN" + std::to_string(i); }
constexpr int INTERVAL = 10;
constexpr int START_Y_POS = 57;

InventoryManager::InventoryManager() :
    _maxInven(0) {
    Core::GetInstance()->AddUpdate(this);
}

InventoryManager::~InventoryManager() {
    for (Item* item : _inventory)
        delete item;
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

// ��° ������. �ε��� ���� ������ �ƴ�
bool InventoryManager::useItem(Entity* user, int i) {
    if (--i < 0 || _inventory.size() <= i)
        return false;

    _inventory[i]->useItem(user);
    // ��� �� ����
    delete _inventory[i];
    _inventory.erase(_inventory.begin() + i);

    resetItemUI();

    return true;
}

void InventoryManager::resetItemUI() {
    // ���� �����ع����� ��ȿ����, ������ ���� �ε����� ���� ���Ѿ� �ҵ�
    for (int i = 1; i <= _inventory.size(); ++i) {
        std::string str = std::format("{} : {}", i, _inventory[i - 1]->getName());
        std::wstring wstr = to_wstring(str);
        UISupporter::GetInstance()->setUI(INVEN(i), wstr);
        UISupporter::GetInstance()->setUI(INVEN(i), (i - 1) * INTERVAL, START_Y_POS);
    }
}

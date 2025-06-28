#pragma once

#include <vector>
#include <queue>

#include "Singletone.h"
#include "Item.h"
#include "IUpdate.h"

class InventoryManager : public Singleton<InventoryManager>, public IUpdate
{
public:
    InventoryManager();
    ~InventoryManager();

public:
    void init(int maxInven);
    bool tryAddItem(Item* item);

    // IUpdate을(를) 통해 상속됨
    void Update() override;
    int GetUpdatePriotity() override;

    bool useItem(Entity* user, int i);

private:
    void resetItemUI();

private:
    int _maxInven;
    std::vector<Item*> _inventory;
    std::queue<Item*> _deActivationQueue;
};


#pragma once

#include <vector>

#include "Singletone.h"
#include "Item.h"

class InventoryManager : public Singleton<InventoryManager>
{
public:
    InventoryManager();

public:
    //void init(int maxInven);
    //void getItem(Item&& item);

private:
    int _maxInven;
    std::vector<Item> _inventory;
};


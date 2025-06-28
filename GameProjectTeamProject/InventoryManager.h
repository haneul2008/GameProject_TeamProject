#pragma once

#include <vector>
#include <queue>

#include "Singletone.h"
#include "Item.h"
#include "IUpdate.h"
#include "IInputable.h"

class InventoryManager : public Singleton<InventoryManager>, public IUpdate, public IInputable
{
public:
    InventoryManager();
    ~InventoryManager() override;

public:
    void init(int maxInven);
    bool tryAddItem(Item* item);

    // IUpdate��(��) ���� ��ӵ�
    void Update() override;
    int GetUpdatePriotity() override;

    bool useItem(Entity* user, int i);
    void resetItemUI();

    // IInputable��(��) ���� ��ӵ�
    void onInputKey(Key key) override;

private:
    int _maxInven;
    bool _openIven;
    std::vector<Item*> _inventory;
    std::queue<Item*> _deActivationQueue;
};


#pragma once

#include<vector>
#include<set>
#include "Singletone.h"
#include "TempEnums.h"
#include "IUpdate.h"
#include "IInputable.h"

struct InputKeyPair
{
    int keyCode;
    Key keyValue;
};

class InputManager : public Singleton<InputManager>, public IUpdate
{
public:
    InputManager();
    ~InputManager() override;

public:
    Key getKey();

    void setInput(bool value);

    void addInputKeyPair(InputKeyPair inputKeyPair);

    bool addInputListener(IInputable* listener);
    bool removeInputListener(IInputable* listener);
    bool containsInputListener(IInputable* listener);
    void clearInputListener();

    // IUpdate��(��) ���� ��ӵ�
    void Update() override;
    int GetUpdatePriotity() override;
    void SetUpdatePriotity(int priority);

private:
    std::vector<InputKeyPair> _inputKeyPairs;
    std::set<IInputable*> _listeners;
    bool _inputLock;
    int _updatePriority;
};

#include "TempEnums.h"
void pauseToWaitInputKey(Key key, unsigned int waitFrame = 15);
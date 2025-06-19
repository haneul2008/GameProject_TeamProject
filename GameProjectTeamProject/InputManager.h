#pragma once

#include<set>
#include "Singletone.h"
#include "TempEnums.h"
#include "IUpdate.h"
#include "IInputable.h"

class InputManager : public Singleton<InputManager>, public IUpdate
{
public:
    InputManager();
    ~InputManager() override;

public:
    Key getKey();

    void setInput(bool value);

    bool addInputListener(IInputable* listener);
    bool removeInputListener(IInputable* listener);
    bool containsInputListener(IInputable* listener);
    void clearInputListener();

    // IUpdate을(를) 통해 상속됨
    void Update() override;
    int GetUpdatePriotity() override;
    void SetUpdatePriotity(int priority);

private:
    std::set<IInputable*> _listeners;
    bool _inputLock;
    int _updatePriority;
};


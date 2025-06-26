#include "InputSystem.h"

#include<windows.h>

#include "Console.h"
#include "Core.h"

InputManager::InputManager() {
    _inputLock = false;
    _updatePriority = 0;
    Core::GetInstance()->AddUpdate(this);
}

InputManager::~InputManager() {
    clearInputListener();
}

Key InputManager::getKey() {
    if (_inputLock)
        return Key::FAIL;

    for (InputKeyPair keyPair : _inputKeyPairs) {
        if ((GetAsyncKeyState(keyPair.keyCode) & 0x0001) != 0)
            return keyPair.keyValue;
    }

    return Key::FAIL;
}

void InputManager::setInput(bool value) {
    _inputLock = value;
}

void InputManager::addInputKeyPair(InputKeyPair inputKeyPair) {
    _inputKeyPairs.push_back(std::move(inputKeyPair));
}

bool InputManager::addInputListener(IInputable* listener) {
    bool success = _listeners.find(listener) == _listeners.end();
    if (success)
        _listeners.insert(listener);
    return success;
}

bool InputManager::removeInputListener(IInputable* listener) {
    bool success = _listeners.find(listener) != _listeners.end();
    if (success)
        _listeners.erase(listener);
    return success;
}

bool InputManager::containsInputListener(IInputable* listener) {
    return _listeners.contains(listener);
}

void InputManager::clearInputListener() {
    _listeners.clear();
}

void InputManager::Update() {
    Key inputKey = getKey();

    if (inputKey != Key::FAIL)
        for (IInputable* listener : _listeners)
            listener->onInputKey(inputKey);
}

int InputManager::GetUpdatePriotity() {
    return _updatePriority;
}

void InputManager::SetUpdatePriotity(int priority) {
    _updatePriority = priority;
}

void pauseToWaitInputKey(Key key, unsigned int waitFrame) {
    while (true) {
        Key inputKey = InputManager::GetInstance()->getKey();

        if (inputKey == key)
            break;

        FrameSync(waitFrame);
    }
}
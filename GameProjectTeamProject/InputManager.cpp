#include "InputManager.h"

#include<windows.h>
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

    // UI키 우선함.
    // 으뜸은 커멘드 입력
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        return Key::READYINPUT;
    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
        return Key::ENDINPUT;

    if (GetAsyncKeyState('I') & 0x8000)
        return Key::OPENINVEN;
    if (GetAsyncKeyState('B') & 0x8000)
        return Key::OPENINVEN;

    if (GetAsyncKeyState('F') & 0x8000)
        return Key::INTERACT;

    if (GetAsyncKeyState(VK_UP) & 0x8000)
        return Key::UP;
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        return Key::DOWN;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        return Key::LEFT;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        return Key::RIGHT;

    if (GetAsyncKeyState('W') & 0x8000)
        return Key::UP;
    if (GetAsyncKeyState('S') & 0x8000)
        return Key::DOWN;
    if (GetAsyncKeyState('A') & 0x8000)
        return Key::LEFT;
    if (GetAsyncKeyState('D') & 0x8000)
        return Key::RIGHT;

    return Key::FAIL;
}

void InputManager::setInput(bool value) {
    _inputLock = value;
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

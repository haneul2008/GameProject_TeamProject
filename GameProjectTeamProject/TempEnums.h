#pragma once

// 머지 충돌을 막기위함.
// InputManager, IInputable used

enum class Key
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OPENINVEN,
    READYINPUT,
    ENDINPUT,
    INTERACT,
    FAIL,
    END
};

enum class Layer
{
    DEFAULT,
    ITEM,
    ENEMY,
    PLAYER,
    WALL,
    STAIR,
    END
};

constexpr int L(Layer l) {
    return 1 << (int)l;
}

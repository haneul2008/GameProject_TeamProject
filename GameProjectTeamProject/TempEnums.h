#pragma once

// ���� �浹�� ��������.
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

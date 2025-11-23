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
    ESC,
    FAIL,
    // 무식하기 그지 없지만 후dp 개선하도록 함.
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,

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

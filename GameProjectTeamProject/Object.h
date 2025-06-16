#pragma once

#include<vector>
#include <utility>
#include<map>

typedef struct Position
{
public:
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

public:
    int x;
    int y;
} Position, * pPosition, Pos, * pPos;

typedef class ObjectRenderInfo
{
public:
    ObjectRenderInfo(wchar_t  defaultImage);
    ~ObjectRenderInfo();

public:
    wchar_t  defaultImage;

private:
    int _currentFrame;
    char _currentAnimationName;
    std::map<char, std::vector<wchar_t >> _animation;

public:
    void addAnimation(char name, std::vector<wchar_t >&& animation);
    // std::vector<char>& GetAnimation(char name);
    void setCurrentAnimation(char name);
    wchar_t getCurrentAndAdvanceFrame();

} RenderInfo, *pRenderInfo, RendI, *pRendI;

typedef class Object
{
public:
    Object(wchar_t defaultImage);
    virtual ~Object();

public:
    Pos pos;
    RendI render;
} Object, *pObject, Obj, *pObj;


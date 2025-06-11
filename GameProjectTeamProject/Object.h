#pragma once

#include<vector>
#include <utility>
#include<map>

typedef struct Position
{
public:
    int x;
    int y;
} Position, * pPosition, Pos, * pPos;

typedef class ObjectRenderInfo
{
public:
    ObjectRenderInfo(char defaultImage);
    ~ObjectRenderInfo();

public:
    char defaultImage;

private:
    int _currentFrame;
    char _currentAnimationName;
    std::map<char, std::vector<char>> _animation;

public:
    void addAnimation(char name, std::vector<char>&& animation);
    // std::vector<char>& GetAnimation(char name);
    void setCurrentAnimation(char name);
    char getCurrentAndAdvanceFrame();

} RenderInfo, *pRenderInfo, RendI, *pRendI;

typedef class Object
{
public:
    Object(char defaultImage);
    virtual ~Object();

public:
    Pos pos;
    RendI render;
} Object, *pObject, Obj, *pObj;


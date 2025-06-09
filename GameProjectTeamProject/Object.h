#pragma once

#include<Vector>
#include<map>

typedef struct _Position
{
public:
    int x;
    int y;
} Position, * pPosition, Pos, * pPos;

// dead등 상태에 따른 이미지 추가 가능성 있음
typedef struct _ObjectRenderInfo
{
public:
    char image;
    std::map<char, std::vector<char>> animation;
} RenderInfo, *pRenderInfo, RendI, *pRendI;

typedef struct _Object
{
public:
    Pos pos;
    RendI render;
} Object, *pObject, Obj, *pObj;


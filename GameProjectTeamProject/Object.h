#pragma once

#include<Vector>
#include<map>

typedef struct _Position
{
public:
    int x;
    int y;
} Position, * pPosition, Pos, * pPos;

// dead�� ���¿� ���� �̹��� �߰� ���ɼ� ����
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


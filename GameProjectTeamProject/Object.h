#pragma once

typedef struct _Position
{
public:
    int x;
    int y;
} Position, * p_Position, Pos, * p_Pos;

// dead�� ���¿� ���� �̹��� �߰� ���ɼ� ����
typedef struct _ObjectImage
{
public:
    char image;
} Image, *p_Image;

typedef struct _Object
{
public:
    _Position pos;

};
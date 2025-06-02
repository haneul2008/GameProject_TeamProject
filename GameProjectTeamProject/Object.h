#pragma once

typedef struct _Position
{
public:
    int x;
    int y;
} Position, * p_Position, Pos, * p_Pos;

// dead등 상태에 따른 이미지 추가 가능성 있음
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
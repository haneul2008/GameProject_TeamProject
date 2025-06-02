#pragma once

struct _Position
{
public:
    int x;
    int y;
} Position, * p_Position, Pos, * p_Pos;

struct _ObjectImage
{
public:
    char image;
} Image, *p_Image;

struct _Object
{
public:
    Position pos;

};
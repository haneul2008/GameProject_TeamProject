#pragma once

#include<vector>
#include <utility>
#include<map>

#include "IRender.h"

typedef struct Position
{
public:
    Position& operator=(const Position& other);

    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

    Position operator+(const Position& other) const;
    Position operator-(const Position& other) const;
    Position operator-() const;

public:
    int x;
    int y;
} Position, * pPosition, Pos, * pPos;

typedef class ObjectRenderInfo
{
public:
    ObjectRenderInfo();
    ~ObjectRenderInfo();

public:
    void setDefaultImage(wchar_t  defaultImage);

    void addAnimation(char name, std::vector<wchar_t >&& animation);
    // std::vector<char>& GetAnimation(char name);
    void setCurrentAnimation(char name);
    wchar_t getCurrentAndAdvanceFrame();

public:
    wchar_t defaultImage;

private:
    int _currentFrame;
    char _currentAnimationName;
    std::map<char, std::vector<wchar_t >> _animation;

} RenderInfo, * pRenderInfo, RendI, * pRendI;

typedef class Object : virtual public IRender
{
public:
    Object();
    virtual ~Object();

public:
    void init();
    virtual void active();
    virtual void deActive();

    void setDefaultImage(wchar_t defaultImage);

    // IRender��(��) ���� ��ӵ�
    void Render() override;
    int GetRenderPriotity() override;

public:
    // �ϰ����� ���� �빮�ڷ� �ۼ�
    void SetRenderPriotity(int priotity);

public:
    Pos pos;
    Pos previousPos;
    RendI render;

    // �ڽ� ��ü�� �켱������ �� �ʿ����
private:
    int _renderPriotity = 10;
} Object, * pObject, Obj, * pObj;


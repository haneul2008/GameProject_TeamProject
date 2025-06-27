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

    // IRender을(를) 통해 상속됨
    void Render() override;
    int GetRenderPriotity() override;

public:
    // 일관성을 위해 대문자로 작성
    void SetRenderPriotity(int priotity);

public:
    Pos pos;
    Pos previousPos;
    RendI render;

    // 자식 객체가 우선순위를 알 필요없음
private:
    int _renderPriotity = 10;
} Object, * pObject, Obj, * pObj;


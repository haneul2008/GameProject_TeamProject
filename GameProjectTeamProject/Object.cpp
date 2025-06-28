#include "Object.h"

#include <iostream>
#include<io.h>  
#include<fcntl.h>

#include "Console.h"
#include "Core.h"

ObjectRenderInfo::ObjectRenderInfo():
_currentFrame(0),
_currentAnimationName('n'),
defaultImage(L'N') {
}

ObjectRenderInfo::~ObjectRenderInfo() {
}

void ObjectRenderInfo::setDefaultImage(wchar_t defaultImage) {
    this->defaultImage = defaultImage;
    _currentFrame = 0;
    _currentAnimationName = 0;
}

void ObjectRenderInfo::addAnimation(char name, std::vector<wchar_t>&& animation) {
    _animation[name] = std::move(animation);
}

/*
std::vector<char>& _ObjectRenderInfo::GetAnimation(char name)
{
    // c++ rvo(return value optimizie) c++17
    // 값 리턴에 대한 최적화
    std::map<char, std::vector<char>>::iterator it = _animation.find(name);
    if (it != _animation.end())
        return it->second;
    //return ;
}
*/

void ObjectRenderInfo::setCurrentAnimation(char name) {
    _currentAnimationName = name;
}

wchar_t ObjectRenderInfo::getCurrentAndAdvanceFrame() {
    std::map<char, std::vector<wchar_t >>::iterator it = _animation.find(_currentAnimationName);
    if (it != _animation.end()) {
        // 현재 프래임 애니메이션 저장시키고 프레임 넘어감
        wchar_t  curAnim = it->second[_currentFrame];
        _currentFrame = (_currentFrame + 1) % it->second.size();
        return curAnim;
    }
    else
        return defaultImage;
}

Object::Object() :
    _renderPriotity(0),
    pos(Pos()),
    previousPos(pos) {
}

Object::~Object() {
}

void Object::init() {
    // 본래 있었음
}

void Object::active() {
    Core::GetInstance()->AddRender(this);
}

void Object::deActive() {
    Core::GetInstance()->RemoveRender(this);
}

Object* Object::newClone() {
    return new Object(*this);
}

void Object::setPosition(const Pos& pos) {
    this->pos = pos;
}

void Object::setDefaultImage(wchar_t defaultImage) {
    render = RendI();
    render.setDefaultImage(defaultImage);
    _renderPriotity = 0;
}

void Object::Render() {
    if (previousPos != pos) {
        MoveCursor(previousPos.x, previousPos.y);
        std::cout << "  ";
    }

    // ㅁ벽등은 2칸을 차지하기에 이를 보간, 하드코딩이라 나중에 짬나면 바꿀 예정
    MoveCursor(pos.x * 2, pos.y);
    wchar_t sprite = render.getCurrentAndAdvanceFrame();
    int coutMode = _setmode(_fileno(stdout), _O_U16TEXT);
    std::wcout << sprite;
    int wcoutMode = _setmode(_fileno(stdout), coutMode);
}

int Object::GetRenderPriotity() {
    return _renderPriotity;
}

void Object::SetRenderPriotity(int priotity) {
    _renderPriotity = priotity;
}

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        this->x = other.x;
        this->y = other.y;
    }

    return *this;
}

bool Position::operator==(const Position& other) const {
    return (x == other.x) && (y == other.y);
}

bool Position::operator!=(const Position& other) const {
    return (x != other.x) && (y != other.y);
}

Position Position::operator+(const Position& other) const {
    Position pos = Position();
    pos = { x + other.x, y + other.y };

    return pos;
}

Position Position::operator-(const Position& other) const {
    return *this + -other;
}

Position Position::operator-() const {
    return Position(-x, -y);
}

int Position::getMagnitude() const {
    return x > y ? x : y;
}

void Position::normalize() {
    x = x == 0 ? 0 : x > 0 ? 1 : -1;
    y = y == 0 ? 0 : y > 0 ? 1 : -1;
}

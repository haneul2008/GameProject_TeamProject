#include "Object.h"

ObjectRenderInfo::ObjectRenderInfo(wchar_t defaultImage)
    :defaultImage(defaultImage)
{
    _currentFrame = 0;
    _currentAnimationName = 0;
}

ObjectRenderInfo::~ObjectRenderInfo()
{

}

void ObjectRenderInfo::addAnimation(char name, std::vector<wchar_t>&& animation)
{
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

void ObjectRenderInfo::setCurrentAnimation(char name)
{
    _currentAnimationName = name;
}

wchar_t ObjectRenderInfo::getCurrentAndAdvanceFrame()
{
    std::map<char, std::vector<wchar_t >>::iterator it = _animation.find(_currentAnimationName);
    if (it != _animation.end())
    {
        // 현재 프래임 애니메이션 저장시키고 프레임 넘어감
        wchar_t  curAnim = it->second[_currentFrame];
        _currentFrame = (_currentFrame + 1) % it->second.size();
        return curAnim;
    }
    else
        return defaultImage;
}

Object::Object(wchar_t defaultImage)
    :render(ObjectRenderInfo(defaultImage)),
    pos(Pos())
{
}

Object::~Object()
{

}

bool Position::operator==(const Position& other) const
{
    return (x == other.x) && (y == other.y);
}

bool Position::operator!=(const Position& other) const
{
    return (x != other.x) && (y != other.y);
}
